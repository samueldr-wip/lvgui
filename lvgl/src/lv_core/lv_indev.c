/**
 * @file lv_indev_proc.c
 *
 */

/*********************
 *      INCLUDES
 ********************/
#include "lv_indev.h"
#include "lv_disp.h"
#include "lv_obj.h"

#include "../lv_hal/lv_hal_tick.h"
#include "../lv_core/lv_group.h"
#include "../lv_core/lv_refr.h"
#include "../lv_misc/lv_task.h"
#include "../lv_misc/lv_math.h"

/*********************
 *      DEFINES
 *********************/

#if LV_INDEV_DEF_DRAG_THROW <= 0
#warning "LV_INDEV_DRAG_THROW must be greater than 0"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void indev_pointer_proc(lv_indev_t * i, lv_indev_data_t * data);
static void indev_keypad_proc(lv_indev_t * i, lv_indev_data_t * data);
static void indev_encoder_proc(lv_indev_t * i, lv_indev_data_t * data);
static void indev_button_proc(lv_indev_t * i, lv_indev_data_t * data);
static void indev_proc_press(lv_indev_proc_t * proc);
static void indev_proc_release(lv_indev_proc_t * proc);
static void indev_proc_reset_query_handler(lv_indev_t * indev);
static lv_obj_t * indev_search_obj(const lv_indev_proc_t * proc, lv_obj_t * obj);
static void indev_drag(lv_indev_proc_t * state);
static void indev_drag_throw(lv_indev_proc_t * proc);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_indev_t * indev_act;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize the display input device subsystem
 */
void lv_indev_init(void)
{
    lv_indev_reset(NULL); /*Reset all input devices*/
}

/**
 * Called periodically to read the input devices
 * @param param pointer to and input device to read
 */
void lv_indev_read_task(void * param)
{
    LV_LOG_TRACE("indev read task started");

    lv_indev_data_t data;

    indev_act = param;

    /*Read and process all indevs*/
    if(indev_act->driver.disp == NULL) return; /*Not assigned to any displays*/

    /*Handle reset query before processing the point*/
    indev_proc_reset_query_handler(indev_act);

    if(indev_act->proc.disabled) return;
    bool more_to_read;
    do {
        /*Read the data*/
        more_to_read = lv_indev_read(indev_act, &data);

        /*The active object might deleted even in the read function*/
        indev_proc_reset_query_handler(indev_act);

        indev_act->proc.state = data.state;

        if(indev_act->proc.state == LV_INDEV_STATE_PR) {
            indev_act->driver.disp->last_activity_time = lv_tick_get();
        }
        if(indev_act->driver.type == LV_INDEV_TYPE_POINTER) {
            indev_pointer_proc(indev_act, &data);
        } else if(indev_act->driver.type == LV_INDEV_TYPE_KEYPAD) {
            indev_keypad_proc(indev_act, &data);
        } else if(indev_act->driver.type == LV_INDEV_TYPE_ENCODER) {
            indev_encoder_proc(indev_act, &data);
        } else if(indev_act->driver.type == LV_INDEV_TYPE_BUTTON) {
            indev_button_proc(indev_act, &data);
        }
        /*Handle reset query if it happened in during processing*/
        indev_proc_reset_query_handler(indev_act);
    } while(more_to_read);

    /*End of indev processing, so no act indev*/
    indev_act = NULL;

    LV_LOG_TRACE("indev read task finished");
}

/**
 * Get the currently processed input device. Can be used in action functions too.
 * @return pointer to the currently processed input device or NULL if no input device processing
 * right now
 */
lv_indev_t * lv_indev_get_act(void)
{
    return indev_act;
}

/**
 * Get the type of an input device
 * @param indev pointer to an input device
 * @return the type of the input device from `lv_hal_indev_type_t` (`LV_INDEV_TYPE_...`)
 */
lv_indev_type_t lv_indev_get_type(const lv_indev_t * indev)
{
    if(indev == NULL) return LV_INDEV_TYPE_NONE;

    return indev->driver.type;
}
/**
 * Reset one or all input devices
 * @param indev pointer to an input device to reset or NULL to reset all of them
 */
void lv_indev_reset(lv_indev_t * indev)
{
    if(indev)
        indev->proc.reset_query = 1;
    else {
        lv_indev_t * i = lv_indev_get_next(NULL);
        while(i) {
            i->proc.reset_query = 1;

            i = lv_indev_get_next(i);
        }
    }
}

/**
 * Reset the long press state of an input device
 * @param indev pointer to an input device
 */
void lv_indev_reset_long_press(lv_indev_t * indev)
{
    indev->proc.long_pr_sent         = 0;
    indev->proc.longpr_rep_timestamp = lv_tick_get();
    indev->proc.pr_timestamp         = lv_tick_get();
}

/**
 * Enable or disable an input devices
 * @param indev pointer to an input device
 * @param en true: enable; false: disable
 */
void lv_indev_enable(lv_indev_t * indev, bool en)
{
    if(!indev) return;

    indev->proc.disabled = en ? 1 : 0;
}

/**
 * Set a cursor for a pointer input device (for LV_INPUT_TYPE_POINTER and LV_INPUT_TYPE_BUTTON)
 * @param indev pointer to an input device
 * @param cur_obj pointer to an object to be used as cursor
 */
void lv_indev_set_cursor(lv_indev_t * indev, lv_obj_t * cur_obj)
{
    if(indev->driver.type != LV_INDEV_TYPE_POINTER) return;

    indev->cursor = cur_obj;
    lv_obj_set_parent(indev->cursor, lv_disp_get_layer_sys(indev->driver.disp));
    lv_obj_set_pos(indev->cursor, indev->proc.types.pointer.act_point.x,
                   indev->proc.types.pointer.act_point.y);
}

#if LV_USE_GROUP
/**
 * Set a destination group for a keypad input device (for LV_INDEV_TYPE_KEYPAD)
 * @param indev pointer to an input device
 * @param group point to a group
 */
void lv_indev_set_group(lv_indev_t * indev, lv_group_t * group)
{
    if(indev->driver.type == LV_INDEV_TYPE_KEYPAD || indev->driver.type == LV_INDEV_TYPE_ENCODER) {
        indev->group = group;
    }
}
#endif

/**
 * Set the an array of points for LV_INDEV_TYPE_BUTTON.
 * These points will be assigned to the buttons to press a specific point on the screen
 * @param indev pointer to an input device
 * @param group point to a group
 */
void lv_indev_set_button_points(lv_indev_t * indev, const lv_point_t * points)
{
    if(indev->driver.type == LV_INDEV_TYPE_BUTTON) {
        indev->btn_points = points;
    }
}

/**
 * Set feedback callback for indev.
 * @param indev pointer to an input device
 * @param feedback feedback callback
 */
void lv_indev_set_feedback(lv_indev_t * indev, lv_indev_feedback_t feedback)
{
    indev->feedback = feedback;
}

/**
 * Get the last point of an input device (for LV_INDEV_TYPE_POINTER and LV_INDEV_TYPE_BUTTON)
 * @param indev pointer to an input device
 * @param point pointer to a point to store the result
 */
void lv_indev_get_point(const lv_indev_t * indev, lv_point_t * point)
{
    if(indev->driver.type != LV_INDEV_TYPE_POINTER && indev->driver.type != LV_INDEV_TYPE_BUTTON) {
        point->x = -1;
        point->y = -1;
    } else {
        point->x = indev->proc.types.pointer.act_point.x;
        point->y = indev->proc.types.pointer.act_point.y;
    }
}

/**
 * Get the last pressed key of an input device (for LV_INDEV_TYPE_KEYPAD)
 * @param indev pointer to an input device
 * @return the last pressed key (0 on error)
 */
uint32_t lv_indev_get_key(const lv_indev_t * indev)
{
    if(indev->driver.type != LV_INDEV_TYPE_KEYPAD)
        return 0;
    else
        return indev->proc.types.keypad.last_key;
}

/**
 * Check if there is dragging with an input device or not (for LV_INDEV_TYPE_POINTER and
 * LV_INDEV_TYPE_BUTTON)
 * @param indev pointer to an input device
 * @return true: drag is in progress
 */
bool lv_indev_is_dragging(const lv_indev_t * indev)
{
    if(indev == NULL) return false;
    if(indev->driver.type != LV_INDEV_TYPE_POINTER && indev->driver.type != LV_INDEV_TYPE_BUTTON)
        return false;
    return indev->proc.types.pointer.drag_in_prog == 0 ? false : true;
}

/**
 * Get the types.pointer.vector of dragging of an input device (for LV_INDEV_TYPE_POINTER and
 * LV_INDEV_TYPE_BUTTON)
 * @param indev pointer to an input device
 * @param point pointer to a point to store the types.pointer.vector
 */
void lv_indev_get_vect(const lv_indev_t * indev, lv_point_t * point)
{
    if(indev == NULL) {
        point->x = 0;
        point->y = 0;
        return;
    }

    if(indev->driver.type != LV_INDEV_TYPE_POINTER && indev->driver.type != LV_INDEV_TYPE_BUTTON) {
        point->x = 0;
        point->y = 0;
    } else {
        point->x = indev->proc.types.pointer.vect.x;
        point->y = indev->proc.types.pointer.vect.y;
    }
}

/**
 * Get feedback callback for indev.
 * @param indev pointer to an input device
 * @return feedback callback
 */
lv_indev_feedback_t lv_indev_get_feedback(const lv_indev_t * indev)
{
    return indev->feedback;
}

/**
 * Do nothing until the next release
 * @param indev pointer to an input device
 */
void lv_indev_wait_release(lv_indev_t * indev)
{
    indev->proc.wait_until_release = 1;
}

/**
 * Get a pointer to the indev read task to
 * modify its parameters with `lv_task_...` functions.
 * @param indev pointer to an input device
 * @return pointer to the indev read refresher task. (NULL on error)
 */
lv_task_t * lv_indev_get_read_task(lv_disp_t * indev)
{
    if(!indev) {
        LV_LOG_WARN("lv_indev_get_read_task: indev was NULL");
        return NULL;
    }

    return indev->refr_task;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Process a new point from LV_INDEV_TYPE_POINTER input device
 * @param i pointer to an input device
 * @param data pointer to the data read from the input device
 */
static void indev_pointer_proc(lv_indev_t * i, lv_indev_data_t * data)
{
    /*Move the cursor if set and moved*/
    if(i->cursor != NULL && (i->proc.types.pointer.last_point.x != data->point.x ||
                             i->proc.types.pointer.last_point.y != data->point.y)) {
        lv_obj_set_pos(i->cursor, data->point.x, data->point.y);
    }

    i->proc.types.pointer.act_point.x = data->point.x;
    i->proc.types.pointer.act_point.y = data->point.y;

    if(i->proc.state == LV_INDEV_STATE_PR) {
        indev_proc_press(&i->proc);
    } else {
        indev_proc_release(&i->proc);
    }

    i->proc.types.pointer.last_point.x = i->proc.types.pointer.act_point.x;
    i->proc.types.pointer.last_point.y = i->proc.types.pointer.act_point.y;
}

/**
 * Process a new point from LV_INDEV_TYPE_KEYPAD input device
 * @param i pointer to an input device
 * @param data pointer to the data read from the input device
 */
static void indev_keypad_proc(lv_indev_t * i, lv_indev_data_t * data)
{
#if LV_USE_GROUP
    if(data->state == LV_INDEV_STATE_PR && i->proc.wait_until_release) return;

    if(i->proc.wait_until_release) {
        i->proc.wait_until_release      = 0;
        i->proc.pr_timestamp            = 0;
        i->proc.long_pr_sent            = 0;
        i->proc.types.keypad.last_state = LV_INDEV_STATE_REL; /*To skip the processing of release*/
    }

    lv_group_t * g = i->group;
    if(g == NULL) return;

    lv_obj_t * focused = lv_group_get_focused(g);
    if(focused == NULL) return;

    /*Save the last key to compare it with the current latter on RELEASE*/
    uint32_t prev_key = i->proc.types.keypad.last_key;

    /* Save the last key.
     * It must be done here else `lv_indev_get_key` will return the last key in events and signals*/
    i->proc.types.keypad.last_key = data->key;

    /* Save the previous state so we can detect state changes below and also set the last state now
     * so if any signal/event handler on the way returns `LV_RES_INV` the last state is remembered
     * for the next time*/
    uint32_t prev_state             = i->proc.types.keypad.last_state;
    i->proc.types.keypad.last_state = data->state;

    /*Key press happened*/
    if(data->state == LV_INDEV_STATE_PR && prev_state == LV_INDEV_STATE_REL) {
        i->proc.pr_timestamp = lv_tick_get();

        /*Simulate a press on the object if ENTER was pressed*/
        if(data->key == LV_GROUP_KEY_ENTER) {
            focused->signal_cb(focused, LV_SIGNAL_PRESSED, NULL);
            if(i->proc.reset_query) return; /*The object might be deleted*/
            lv_event_send(focused, LV_EVENT_PRESSED, NULL);
            if(i->proc.reset_query) return; /*The object might be deleted*/

            /*Send the ENTER as a normal KEY*/
            lv_group_send_data(g, LV_GROUP_KEY_ENTER);
        }
        /*Move the focus on NEXT*/
        else if(data->key == LV_GROUP_KEY_NEXT) {
            lv_group_set_editing(g,
                                 false); /*Editing is not used by KEYPAD is be sure it is disabled*/
            lv_group_focus_next(g);
            if(i->proc.reset_query) return; /*The object might be deleted*/
        }
        /*Move the focus on PREV*/
        else if(data->key == LV_GROUP_KEY_PREV) {
            lv_group_set_editing(g,
                                 false); /*Editing is not used by KEYPAD is be sure it is disabled*/
            lv_group_focus_prev(g);
            if(i->proc.reset_query) return; /*The object might be deleted*/
        }
        /*Just send other keys to the object (e.g. 'A' or `LV_GORUP_KEY_RIGHT)*/
        else {
            lv_group_send_data(g, data->key);
        }
    }
    /*Pressing*/
    else if(data->state == LV_INDEV_STATE_PR && prev_state == LV_INDEV_STATE_PR) {
        /*Long press time has elapsed?*/
        if(i->proc.long_pr_sent == 0 &&
           lv_tick_elaps(i->proc.pr_timestamp) > i->driver.long_press_time) {
            i->proc.long_pr_sent = 1;
            if(data->key == LV_GROUP_KEY_ENTER) {
                i->proc.longpr_rep_timestamp = lv_tick_get();
                focused->signal_cb(focused, LV_SIGNAL_LONG_PRESS, NULL);
                if(i->proc.reset_query) return; /*The object might be deleted*/
                lv_event_send(focused, LV_EVENT_LONG_PRESSED, NULL);
                if(i->proc.reset_query) return; /*The object might be deleted*/
            }
        }
        /*Long press repeated time has elapsed?*/
        else if(i->proc.long_pr_sent != 0 &&
                lv_tick_elaps(i->proc.longpr_rep_timestamp) > i->driver.long_press_rep_time) {

            i->proc.longpr_rep_timestamp = lv_tick_get();

            /*Send LONG_PRESS_REP on ENTER*/
            if(data->key == LV_GROUP_KEY_ENTER) {
                focused->signal_cb(focused, LV_SIGNAL_LONG_PRESS_REP, NULL);
                if(i->proc.reset_query) return; /*The object might be deleted*/
                lv_event_send(focused, LV_EVENT_LONG_PRESSED_REPEAT, NULL);
                if(i->proc.reset_query) return; /*The object might be deleted*/
            }
            /*Move the focus on NEXT again*/
            else if(data->key == LV_GROUP_KEY_NEXT) {
                lv_group_set_editing(
                    g, false); /*Editing is not used by KEYPAD is be sure it is disabled*/
                lv_group_focus_next(g);
                if(i->proc.reset_query) return; /*The object might be deleted*/
            }
            /*Move the focus on PREV again*/
            else if(data->key == LV_GROUP_KEY_PREV) {
                lv_group_set_editing(
                    g, false); /*Editing is not used by KEYPAD is be sure it is disabled*/
                lv_group_focus_prev(g);
                if(i->proc.reset_query) return; /*The object might be deleted*/
            }
            /*Just send other keys again to the object (e.g. 'A' or `LV_GORUP_KEY_RIGHT)*/
            else {
                lv_group_send_data(g, data->key);
                if(i->proc.reset_query) return; /*The object might be deleted*/
            }
        }
    }
    /*Release happened*/
    else if(data->state == LV_INDEV_STATE_REL && prev_state == LV_INDEV_STATE_PR) {
        /*The user might clear the key when it was released. Always release the pressed key*/
        data->key = prev_key;
        if(data->key == LV_GROUP_KEY_ENTER) {

            focused->signal_cb(focused, LV_SIGNAL_RELEASED, NULL);
            if(i->proc.reset_query) return; /*The object might be deleted*/

            if(i->proc.long_pr_sent == 0) {
                lv_event_send(focused, LV_EVENT_SHORT_CLICKED, NULL);
            }

            lv_event_send(focused, LV_EVENT_CLICKED, NULL);
            if(i->proc.reset_query) return; /*The object might be deleted*/

            lv_event_send(focused, LV_EVENT_RELEASED, NULL);
            if(i->proc.reset_query) return; /*The object might be deleted*/
        }
        i->proc.pr_timestamp = 0;
        i->proc.long_pr_sent = 0;
    }
#else
    (void)data; /*Unused*/
    (void)i;    /*Unused*/
#endif
}

/**
 * Process a new point from LV_INDEV_TYPE_ENCODER input device
 * @param i pointer to an input device
 * @param data pointer to the data read from the input device
 */
static void indev_encoder_proc(lv_indev_t * i, lv_indev_data_t * data)
{
#if LV_USE_GROUP

    if(data->state == LV_INDEV_STATE_PR && i->proc.wait_until_release) return;

    if(i->proc.wait_until_release) {
        i->proc.wait_until_release      = 0;
        i->proc.pr_timestamp            = 0;
        i->proc.long_pr_sent            = 0;
        i->proc.types.keypad.last_state = LV_INDEV_STATE_REL; /*To skip the processing of release*/
    }

    lv_group_t * g = i->group;
    if(g == NULL) return;

    lv_obj_t * focused = lv_group_get_focused(g);
    if(focused == NULL) return;

    /*Process the steps first. They are valid only with released button*/
    if(data->state == LV_INDEV_STATE_REL) {
        /*In edit mode send LEFT/RIGHT keys*/
        if(lv_group_get_editing(g)) {
            int32_t s;
            if(data->enc_diff < 0) {
                for(s = 0; s < -data->enc_diff; s++) lv_group_send_data(g, LV_GROUP_KEY_LEFT);
            } else if(data->enc_diff > 0) {
                for(s = 0; s < data->enc_diff; s++) lv_group_send_data(g, LV_GROUP_KEY_RIGHT);
            }
        }
        /*In navigate mode focus on the next/prev objects*/
        else {
            int32_t s;
            if(data->enc_diff < 0) {
                for(s = 0; s < -data->enc_diff; s++) lv_group_focus_prev(g);
            } else if(data->enc_diff > 0) {
                for(s = 0; s < data->enc_diff; s++) lv_group_focus_next(g);
            }
        }
    }

    /*Refresh the focused object. It might change due to lv_group_focus_prev/next*/
    focused = lv_group_get_focused(g);
    if(focused == NULL) return;

    /*Button press happened*/
    if(data->state == LV_INDEV_STATE_PR && i->proc.types.keypad.last_state == LV_INDEV_STATE_REL) {
        bool editable = false;
        focused->signal_cb(focused, LV_SIGNAL_GET_EDITABLE, &editable);

        i->proc.pr_timestamp = lv_tick_get();
        if(lv_group_get_editing(g) == true || editable == false) {
            focused->signal_cb(focused, LV_SIGNAL_PRESSED, NULL);
            if(i->proc.reset_query) return; /*The object might be deleted*/

            lv_event_send(focused, LV_EVENT_PRESSED, NULL);
            if(i->proc.reset_query) return; /*The object might be deleted*/
        }
    }
    /*Pressing*/
    else if(data->state == LV_INDEV_STATE_PR &&
            i->proc.types.keypad.last_state == LV_INDEV_STATE_PR) {
        if(i->proc.long_pr_sent == 0 &&
           lv_tick_elaps(i->proc.pr_timestamp) > i->driver.long_press_time) {
            bool editable = false;
            focused->signal_cb(focused, LV_SIGNAL_GET_EDITABLE, &editable);

            /*On enter long press toggle edit mode.*/
            if(editable) {
                /*Don't leave edit mode if there is only one object (nowhere to navigate)*/
                if(lv_ll_is_empty(&g->obj_ll) == false) {
                    lv_group_set_editing(g, lv_group_get_editing(g)
                                                ? false
                                                : true); /*Toggle edit mode on long press*/
                }
            }
            /*If not editable then just send a long press signal*/
            else {
                focused->signal_cb(focused, LV_SIGNAL_LONG_PRESS, NULL);
                if(i->proc.reset_query) return; /*The object might be deleted*/
                lv_event_send(focused, LV_EVENT_LONG_PRESSED, NULL);
                if(i->proc.reset_query) return; /*The object might be deleted*/
            }
            i->proc.long_pr_sent = 1;
        }
    }
    /*Release happened*/
    else if(data->state == LV_INDEV_STATE_REL &&
            i->proc.types.keypad.last_state == LV_INDEV_STATE_PR) {

        bool editable = false;
        focused->signal_cb(focused, LV_SIGNAL_GET_EDITABLE, &editable);

        /*The button was released on a non-editable object. Just send enter*/
        if(editable == false) {
            focused->signal_cb(focused, LV_SIGNAL_RELEASED, NULL);
            if(i->proc.reset_query) return; /*The object might be deleted*/

            if(i->proc.long_pr_sent == 0) lv_event_send(focused, LV_EVENT_SHORT_CLICKED, NULL);
            if(i->proc.reset_query) return; /*The object might be deleted*/

            lv_event_send(focused, LV_EVENT_CLICKED, NULL);
            if(i->proc.reset_query) return; /*The object might be deleted*/

            lv_event_send(focused, LV_EVENT_RELEASED, NULL);
            if(i->proc.reset_query) return; /*The object might be deleted*/
        }
        /*An object is being edited and the button is released. */
        else if(g->editing) {
            /*Ignore long pressed enter release because it comes from mode switch*/
            if(!i->proc.long_pr_sent || lv_ll_is_empty(&g->obj_ll)) {
                focused->signal_cb(focused, LV_SIGNAL_RELEASED, NULL);
                if(i->proc.reset_query) return; /*The object might be deleted*/

                lv_event_send(focused, LV_EVENT_SHORT_CLICKED, NULL);
                if(i->proc.reset_query) return; /*The object might be deleted*/

                lv_event_send(focused, LV_EVENT_CLICKED, NULL);
                if(i->proc.reset_query) return; /*The object might be deleted*/

                lv_event_send(focused, LV_EVENT_RELEASED, NULL);
                if(i->proc.reset_query) return; /*The object might be deleted*/

                lv_group_send_data(g, LV_GROUP_KEY_ENTER);
            }
        }
        /*If the focused object is editable and now in navigate mode then on enter switch edit
           mode*/
        else if(editable && !g->editing && !i->proc.long_pr_sent) {
            lv_group_set_editing(g, true); /*Set edit mode*/
        }

        i->proc.pr_timestamp = 0;
        i->proc.long_pr_sent = 0;
    }

    i->proc.types.keypad.last_state = data->state;
    i->proc.types.keypad.last_key   = data->key;
#else
    (void)data; /*Unused*/
    (void)i;    /*Unused*/
#endif
}

/**
 * Process new points from a input device. indev->state.pressed has to be set
 * @param indev pointer to an input device state
 * @param x x coordinate of the next point
 * @param y y coordinate of the next point
 */
static void indev_button_proc(lv_indev_t * i, lv_indev_data_t * data)
{
    i->proc.types.pointer.act_point.x = i->btn_points[data->btn_id].x;
    i->proc.types.pointer.act_point.y = i->btn_points[data->btn_id].y;

    /*Still the same point is pressed*/
    if(i->proc.types.pointer.last_point.x == i->proc.types.pointer.act_point.x &&
       i->proc.types.pointer.last_point.y == i->proc.types.pointer.act_point.y &&
       data->state == LV_INDEV_STATE_PR) {
        indev_proc_press(&i->proc);
    } else {
        /*If a new point comes always make a release*/
        indev_proc_release(&i->proc);
    }

    i->proc.types.pointer.last_point.x = i->proc.types.pointer.act_point.x;
    i->proc.types.pointer.last_point.y = i->proc.types.pointer.act_point.y;
}

/**
 * Process the pressed state of LV_INDEV_TYPE_POINER input devices
 * @param indev pointer to an input device 'proc'
 * @return LV_RES_OK: no indev reset required; LV_RES_INV: indev reset is required
 */
static void indev_proc_press(lv_indev_proc_t * proc)
{
    lv_obj_t * pr_obj = proc->types.pointer.act_obj;

    if(proc->wait_until_release != 0) return;

    lv_disp_t * disp = indev_act->driver.disp;

    /*If there is no last object then search*/
    if(proc->types.pointer.act_obj == NULL) {
        pr_obj = indev_search_obj(proc, lv_disp_get_layer_sys(disp));
        if(pr_obj == NULL) pr_obj = indev_search_obj(proc, lv_disp_get_layer_top(disp));
        if(pr_obj == NULL) pr_obj = indev_search_obj(proc, lv_disp_get_scr_act(disp));
    }
    /*If there is last object but it is not dragged and not protected also search*/
    else if(proc->types.pointer.drag_in_prog == 0 &&
            lv_obj_is_protected(proc->types.pointer.act_obj, LV_PROTECT_PRESS_LOST) ==
                false) { /*Now types.pointer.act_obj != NULL*/
        pr_obj = indev_search_obj(proc, lv_disp_get_layer_sys(disp));
        if(pr_obj == NULL) pr_obj = indev_search_obj(proc, lv_disp_get_layer_top(disp));
        if(pr_obj == NULL) pr_obj = indev_search_obj(proc, lv_disp_get_scr_act(disp));
    }
    /*If a dragable or a protected object was the last then keep it*/
    else {
    }

    /*If a new object was found reset some variables and send a pressed signal*/
    if(pr_obj != proc->types.pointer.act_obj) {

        proc->types.pointer.last_point.x = proc->types.pointer.act_point.x;
        proc->types.pointer.last_point.y = proc->types.pointer.act_point.y;

        /*If a new object found the previous was lost, so send a signal*/
        if(proc->types.pointer.act_obj != NULL) {
            proc->types.pointer.act_obj->signal_cb(proc->types.pointer.act_obj,
                                                   LV_SIGNAL_PRESS_LOST, indev_act);
            if(proc->reset_query) return; /*The object might be deleted*/
            lv_event_send(proc->types.pointer.act_obj, LV_EVENT_PRESS_LOST, NULL);
            if(proc->reset_query) return; /*The object might be deleted*/
        }

        proc->types.pointer.act_obj = pr_obj; /*Save the pressed object*/
        proc->types.pointer.last_obj =
            proc->types.pointer.act_obj; /*Refresh the types.pointer.last_obj*/

        if(proc->types.pointer.act_obj != NULL) {
            /* Save the time when the obj pressed.
             * It is necessary to count the long press time.*/
            proc->pr_timestamp                 = lv_tick_get();
            proc->long_pr_sent                 = 0;
            proc->types.pointer.drag_limit_out = 0;
            proc->types.pointer.drag_in_prog   = 0;
            proc->types.pointer.drag_sum.x     = 0;
            proc->types.pointer.drag_sum.y     = 0;
            proc->types.pointer.vect.x         = 0;
            proc->types.pointer.vect.y         = 0;

            /*Search for 'top' attribute*/
            lv_obj_t * i        = proc->types.pointer.act_obj;
            lv_obj_t * last_top = NULL;
            while(i != NULL) {
                if(i->top != 0) last_top = i;
                i = lv_obj_get_parent(i);
            }

            if(last_top != NULL) {
                /*Move the last_top object to the foreground*/
                lv_obj_t * par = lv_obj_get_parent(last_top);
                /*After list change it will be the new head*/
                lv_ll_chg_list(&par->child_ll, &par->child_ll, last_top);
                lv_obj_invalidate(last_top);
            }

            /*Send a signal about the press*/
            proc->types.pointer.act_obj->signal_cb(proc->types.pointer.act_obj, LV_SIGNAL_PRESSED,
                                                   indev_act);
            if(proc->reset_query) return; /*The object might be deleted*/
            lv_event_send(proc->types.pointer.act_obj, LV_EVENT_PRESSED, NULL);
            if(proc->reset_query) return; /*The object might be deleted*/
        }
    }

    /*Calculate the types.pointer.vector*/
    proc->types.pointer.vect.x = proc->types.pointer.act_point.x - proc->types.pointer.last_point.x;
    proc->types.pointer.vect.y = proc->types.pointer.act_point.y - proc->types.pointer.last_point.y;

    proc->types.pointer.drag_throw_vect.x = (proc->types.pointer.drag_throw_vect.x * 5) >> 3;
    proc->types.pointer.drag_throw_vect.y = (proc->types.pointer.drag_throw_vect.y * 5) >> 3;

    if(proc->types.pointer.drag_throw_vect.x < 0)
        proc->types.pointer.drag_throw_vect.x++;
    else if(proc->types.pointer.drag_throw_vect.x > 0)
        proc->types.pointer.drag_throw_vect.x--;

    if(proc->types.pointer.drag_throw_vect.y < 0)
        proc->types.pointer.drag_throw_vect.y++;
    else if(proc->types.pointer.drag_throw_vect.y > 0)
        proc->types.pointer.drag_throw_vect.y--;

    proc->types.pointer.drag_throw_vect.x += (proc->types.pointer.vect.x * 4) >> 3;
    proc->types.pointer.drag_throw_vect.y += (proc->types.pointer.vect.y * 4) >> 3;

    /*If there is active object and it can be dragged run the drag*/
    if(proc->types.pointer.act_obj != NULL) {
        proc->types.pointer.act_obj->signal_cb(proc->types.pointer.act_obj, LV_SIGNAL_PRESSING,
                                               indev_act);
        if(proc->reset_query) return; /*The object might be deleted*/
        lv_event_send(proc->types.pointer.act_obj, LV_EVENT_PRESSING, NULL);
        if(proc->reset_query) return; /*The object might be deleted*/

        indev_drag(proc);
        if(proc->reset_query != 0) return;

        /*If there is no drag then check for long press time*/
        if(proc->types.pointer.drag_in_prog == 0 && proc->long_pr_sent == 0) {
            /*Send a signal about the long press if enough time elapsed*/
            if(lv_tick_elaps(proc->pr_timestamp) > indev_act->driver.long_press_time) {
                pr_obj->signal_cb(pr_obj, LV_SIGNAL_LONG_PRESS, indev_act);
                if(proc->reset_query) return; /*The object might be deleted*/
                lv_event_send(pr_obj, LV_EVENT_LONG_PRESSED, NULL);
                if(proc->reset_query) return; /*The object might be deleted*/

                /*Mark the signal sending to do not send it again*/
                proc->long_pr_sent = 1;

                /*Save the long press time stamp for the long press repeat handler*/
                proc->longpr_rep_timestamp = lv_tick_get();
            }
        }
        /*Send long press repeated signal*/
        if(proc->types.pointer.drag_in_prog == 0 && proc->long_pr_sent == 1) {
            /*Send a signal about the long press repeate if enough time elapsed*/
            if(lv_tick_elaps(proc->longpr_rep_timestamp) > indev_act->driver.long_press_rep_time) {
                pr_obj->signal_cb(pr_obj, LV_SIGNAL_LONG_PRESS_REP, indev_act);
                if(proc->reset_query) return; /*The object might be deleted*/
                lv_event_send(pr_obj, LV_EVENT_LONG_PRESSED_REPEAT, NULL);
                if(proc->reset_query) return; /*The object might be deleted*/
                proc->longpr_rep_timestamp = lv_tick_get();
            }
        }
    }
}

/**
 * Process the released state of LV_INDEV_TYPE_POINER input devices
 * @param proc pointer to an input device 'proc'
 */
static void indev_proc_release(lv_indev_proc_t * proc)
{
    if(proc->wait_until_release != 0) {
        proc->types.pointer.act_obj  = NULL;
        proc->types.pointer.last_obj = NULL;
        proc->pr_timestamp           = 0;
        proc->longpr_rep_timestamp   = 0;
        proc->wait_until_release     = 0;
    }

    /*Forget the act obj and send a released signal */
    if(proc->types.pointer.act_obj) {
        /* If the object was protected against press lost then it possible that
         * the object is already not pressed but still it is the `act_obj`.
         * In this case send the `LV_SIGNAL_RELEASED/CLICKED` instead of `LV_SIGNAL_PRESS_LOST` if
         * the indev is ON the `types.pointer.act_obj` */
        if(lv_obj_is_protected(proc->types.pointer.act_obj, LV_PROTECT_PRESS_LOST)) {
            proc->types.pointer.act_obj->signal_cb(proc->types.pointer.act_obj, LV_SIGNAL_RELEASED,
                                                   indev_act);
            if(proc->reset_query) return; /*The object might be deleted*/

            if(proc->types.pointer.drag_in_prog == 0) {
                if(proc->long_pr_sent == 0) {
                    lv_event_send(proc->types.pointer.act_obj, LV_EVENT_SHORT_CLICKED, NULL);
                    if(proc->reset_query) return; /*The object might be deleted*/
                }

                lv_event_send(proc->types.pointer.act_obj, LV_EVENT_CLICKED, NULL);
                if(proc->reset_query) return; /*The object might be deleted*/
            }

            lv_event_send(proc->types.pointer.act_obj, LV_EVENT_RELEASED, NULL);
            if(proc->reset_query) return; /*The object might be deleted*/
        }
        /* The simple case: `act_obj` was not protected against press lost.
         * If it is already not pressed then was `indev_proc_press` would set `act_obj = NULL`*/
        else {
            proc->types.pointer.act_obj->signal_cb(proc->types.pointer.act_obj, LV_SIGNAL_RELEASED,
                                                   indev_act);
            if(proc->reset_query) return; /*The object might be deleted*/

            if(proc->long_pr_sent == 0 && proc->types.pointer.drag_in_prog == 0) {
                lv_event_send(proc->types.pointer.act_obj, LV_EVENT_SHORT_CLICKED, NULL);
                if(proc->reset_query) return; /*The object might be deleted*/
            }

            lv_event_send(proc->types.pointer.act_obj, LV_EVENT_CLICKED, NULL);
            if(proc->reset_query) return; /*The object might be deleted*/

            lv_event_send(proc->types.pointer.act_obj, LV_EVENT_RELEASED, NULL);
            if(proc->reset_query) return; /*The object might be deleted*/
        }

        if(proc->reset_query != 0) return;

            /*Handle click focus*/
#if LV_USE_GROUP
        /*Edit mode is not used by POINTER devices. So leave edit mode if we are in it*/
        lv_group_t * g = lv_obj_get_group(proc->types.pointer.act_obj);
        if(lv_group_get_editing(g)) lv_group_set_editing(g, false);

        /*Check, if the parent is in a group focus on it.*/
        if(lv_obj_is_protected(proc->types.pointer.act_obj, LV_PROTECT_CLICK_FOCUS) ==
           false) { /*Respect the click focus protection*/
            lv_obj_t * parent = proc->types.pointer.act_obj;

            while(g == NULL) {
                parent = lv_obj_get_parent(parent);
                if(parent == NULL) break;
                if(lv_obj_is_protected(
                       parent,
                       LV_PROTECT_CLICK_FOCUS)) { /*Ignore is the protected against click focus*/
                    parent = NULL;
                    break;
                }
                g = lv_obj_get_group(parent);
            }

            /* If a pareit is in a group make it focused.
             * `LV_EVENT_FOCUSED/DEFOCUSED` will be sent by `lv_group_focus_obj`*/
            if(g && parent) {
                if(lv_group_get_click_focus(g)) {
                    lv_group_focus_obj(parent);
                }
            }
        }
#endif

        /* Send defocus to the lastly "active" object and foucus to the new one.
         * If the one of them is in group then it possible that `lv_group_focus_obj` alraedy sent
         * a focus/defucus signal because of `click focus`*/
        if(proc->types.pointer.last_pressed != proc->types.pointer.act_obj) {
            lv_event_send(proc->types.pointer.last_pressed, LV_EVENT_DEFOCUSED, NULL);
            if(proc->reset_query)
                return; /*Not so strict as it's only the previous object and indev not uses it.*/

            lv_event_send(proc->types.pointer.act_obj, LV_EVENT_FOCUSED, NULL);
            if(proc->reset_query) return; /*The object might be deleted*/

            proc->types.pointer.last_pressed = proc->types.pointer.act_obj;
        }

        if(proc->reset_query != 0) return;
        proc->types.pointer.act_obj = NULL;
        proc->pr_timestamp          = 0;
        proc->longpr_rep_timestamp  = 0;
    }

    /*The reset can be set in the signal function.
     * In case of reset query ignore the remaining parts.*/
    if(proc->types.pointer.last_obj != NULL && proc->reset_query == 0) {
        indev_drag_throw(proc);
        if(proc->reset_query != 0) return;
    }
}

/**
 * Process a new point from LV_INDEV_TYPE_BUTTON input device
 * @param i pointer to an input device
 * @param data pointer to the data read from the input device
 * Reset input device if a reset query has been sent to it
 * @param indev pointer to an input device
 */
static void indev_proc_reset_query_handler(lv_indev_t * indev)
{
    if(indev->proc.reset_query) {
        indev->proc.types.pointer.act_obj           = NULL;
        indev->proc.types.pointer.last_obj          = NULL;
        indev->proc.types.pointer.last_pressed      = NULL;
        indev->proc.types.pointer.drag_limit_out    = 0;
        indev->proc.types.pointer.drag_in_prog      = 0;
        indev->proc.long_pr_sent                    = 0;
        indev->proc.pr_timestamp                    = 0;
        indev->proc.longpr_rep_timestamp            = 0;
        indev->proc.types.pointer.drag_sum.x        = 0;
        indev->proc.types.pointer.drag_sum.y        = 0;
        indev->proc.types.pointer.drag_throw_vect.x = 0;
        indev->proc.types.pointer.drag_throw_vect.y = 0;
        indev->proc.reset_query                     = 0;
    }
}
/**
 * Search the most top, clickable object on the last point of an input device
 * @param proc pointer to  the `lv_indev_proc_t` part of the input device
 * @param obj pointer to a start object, typically the screen
 * @return pointer to the found object or NULL if there was no suitable object
 */
static lv_obj_t * indev_search_obj(const lv_indev_proc_t * proc, lv_obj_t * obj)
{
    lv_obj_t * found_p = NULL;

    /*If the point is on this object*/
    /*Check its children too*/
    if(lv_area_is_point_on(&obj->coords, &proc->types.pointer.act_point)) {
        lv_obj_t * i;

        LV_LL_READ(obj->child_ll, i)
        {
            found_p = indev_search_obj(proc, i);

            /*If a child was found then break*/
            if(found_p != NULL) {
                break;
            }
        }

        /*If then the children was not ok, and this obj is clickable
         * and it or its parent is not hidden then save this object*/
        if(found_p == NULL && lv_obj_get_click(obj) != false) {
            lv_obj_t * hidden_i = obj;
            while(hidden_i != NULL) {
                if(lv_obj_get_hidden(hidden_i) == true) break;
                hidden_i = lv_obj_get_parent(hidden_i);
            }
            /*No parent found with hidden == true*/
            if(hidden_i == NULL) found_p = obj;
        }
    }

    return found_p;
}

/**
 * Handle the dragging of indev_proc_p->types.pointer.act_obj
 * @param indev pointer to a input device state
 */
static void indev_drag(lv_indev_proc_t * state)
{
    lv_obj_t * drag_obj = state->types.pointer.act_obj;

    /*If drag parent is active check recursively the drag_parent attribute*/
    while(lv_obj_get_drag_parent(drag_obj) != false && drag_obj != NULL) {
        drag_obj = lv_obj_get_parent(drag_obj);
    }

    if(drag_obj == NULL) return;

    if(lv_obj_get_drag(drag_obj) == false) return;

    lv_drag_dir_t allowed_dirs = lv_obj_get_drag_dir(drag_obj);

    /*Count the movement by drag*/
    state->types.pointer.drag_sum.x += state->types.pointer.vect.x;
    state->types.pointer.drag_sum.y += state->types.pointer.vect.y;

    /*Enough move?*/
    if(state->types.pointer.drag_limit_out == 0) {
        /*If a move is greater then LV_DRAG_LIMIT then begin the drag*/
        if(((allowed_dirs & LV_DRAG_DIR_HOR) && LV_MATH_ABS(state->types.pointer.drag_sum.x) >= indev_act->driver.drag_limit) ||
           ((allowed_dirs & LV_DRAG_DIR_VER) && LV_MATH_ABS(state->types.pointer.drag_sum.y) >= indev_act->driver.drag_limit)) {
            state->types.pointer.drag_limit_out = 1;
        }
    }

    /*If the drag limit is exceeded handle the dragging*/
    if(state->types.pointer.drag_limit_out != 0) {
        /*Set new position if the vector is not zero*/
        if(state->types.pointer.vect.x != 0 || state->types.pointer.vect.y != 0) {

            /*Get the coordinates of the object and modify them*/
            lv_coord_t act_x      = lv_obj_get_x(drag_obj);
            lv_coord_t act_y      = lv_obj_get_y(drag_obj);
            uint16_t inv_buf_size = lv_disp_get_inv_buf_size(
                indev_act->driver.disp); /*Get the number of currently invalidated areas*/

            lv_coord_t prev_x     = drag_obj->coords.x1;
            lv_coord_t prev_y     = drag_obj->coords.y1;
            lv_coord_t prev_par_w = lv_obj_get_width(lv_obj_get_parent(drag_obj));
            lv_coord_t prev_par_h = lv_obj_get_height(lv_obj_get_parent(drag_obj));

            if(allowed_dirs & LV_DRAG_DIR_HOR)
            	lv_obj_set_x(drag_obj, act_x + state->types.pointer.vect.x);

            if(allowed_dirs & LV_DRAG_DIR_VER)
            	lv_obj_set_y(drag_obj, act_y + state->types.pointer.vect.y);

            /*Set the drag in progress flag if the object is really moved*/
            if(drag_obj->coords.x1 != prev_x || drag_obj->coords.y1 != prev_y) {
                if(state->types.pointer.drag_in_prog !=
                   0) { /*Send the drag begin signal on first move*/
                    drag_obj->signal_cb(drag_obj, LV_SIGNAL_DRAG_BEGIN, indev_act);
                    if(state->reset_query != 0) return;
                }
                state->types.pointer.drag_in_prog = 1;
            }
            /*If the object didn't moved then clear the invalidated areas*/
            else {
                /*In a special case if the object is moved on a page and
                 * the scrollable has fit == true and the object is dragged of the page then
                 * while its coordinate is not changing only the parent's size is reduced */
                lv_coord_t act_par_w = lv_obj_get_width(lv_obj_get_parent(drag_obj));
                lv_coord_t act_par_h = lv_obj_get_height(lv_obj_get_parent(drag_obj));
                if(act_par_w == prev_par_w && act_par_h == prev_par_h) {
                    uint16_t new_inv_buf_size = lv_disp_get_inv_buf_size(indev_act->driver.disp);
                    lv_disp_pop_from_inv_buf(indev_act->driver.disp,
                                             new_inv_buf_size - inv_buf_size);
                }
            }
        }
    }
}

/**
 * Handle throwing by drag if the drag is ended
 * @param indev pointer to an input device state
 */
static void indev_drag_throw(lv_indev_proc_t * proc)
{
    if(proc->types.pointer.drag_in_prog == 0) return;

    /*Set new position if the vector is not zero*/
    lv_obj_t * drag_obj = proc->types.pointer.last_obj;

    /*If drag parent is active check recursively the drag_parent attribute*/
    while(lv_obj_get_drag_parent(drag_obj) != false && drag_obj != NULL) {
        drag_obj = lv_obj_get_parent(drag_obj);
    }

    if(drag_obj == NULL) {
        return;
    }

    /*Return if the drag throw is not enabled*/
    if(lv_obj_get_drag_throw(drag_obj) == false) {
        proc->types.pointer.drag_in_prog = 0;
        drag_obj->signal_cb(drag_obj, LV_SIGNAL_DRAG_END, indev_act);
        return;
    }

    lv_drag_dir_t allowed_dirs = lv_obj_get_drag_dir(drag_obj);

    /*Reduce the vectors*/
    proc->types.pointer.drag_throw_vect.x =
        proc->types.pointer.drag_throw_vect.x * (100 - indev_act->driver.drag_throw) / 100;
    proc->types.pointer.drag_throw_vect.y =
        proc->types.pointer.drag_throw_vect.y * (100 - indev_act->driver.drag_throw) / 100;

    if(proc->types.pointer.drag_throw_vect.x != 0 || proc->types.pointer.drag_throw_vect.y != 0) {
        /*Get the coordinates and modify them*/
        lv_area_t coords_ori;
        lv_obj_get_coords(drag_obj, &coords_ori);
        lv_coord_t act_x = lv_obj_get_x(drag_obj) + proc->types.pointer.drag_throw_vect.x;
        lv_coord_t act_y = lv_obj_get_y(drag_obj) + proc->types.pointer.drag_throw_vect.y;

        if(allowed_dirs & LV_DRAG_DIR_HOR)
			lv_obj_set_x(drag_obj, act_x );

		if(allowed_dirs & LV_DRAG_DIR_VER)
			lv_obj_set_y(drag_obj, act_y);

        lv_area_t coord_new;
        lv_obj_get_coords(drag_obj, &coord_new);

        /*If non of the coordinates are changed then do not continue throwing*/
        if((coords_ori.x1 == coord_new.x1 || proc->types.pointer.drag_throw_vect.x == 0) &&
           (coords_ori.y1 == coord_new.y1 || proc->types.pointer.drag_throw_vect.y == 0)) {
            proc->types.pointer.drag_in_prog      = 0;
            proc->types.pointer.vect.x            = 0;
            proc->types.pointer.vect.y            = 0;
            proc->types.pointer.drag_throw_vect.x = 0;
            proc->types.pointer.drag_throw_vect.y = 0;
            drag_obj->signal_cb(drag_obj, LV_SIGNAL_DRAG_END, indev_act);
            if(proc->reset_query) return; /*The object might be deleted*/
        }
    }
    /*If the types.pointer.vectors become 0 -> types.pointer.drag_in_prog = 0 and send a drag end
       signal*/
    else {
        proc->types.pointer.drag_in_prog = 0;
        drag_obj->signal_cb(drag_obj, LV_SIGNAL_DRAG_END, indev_act);
        if(proc->reset_query) return; /*The object might be deleted*/
    }
}
