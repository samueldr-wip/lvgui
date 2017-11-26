/**
 * @file lv_slider.c
 * 
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf.h"
#if USE_LV_SLIDER != 0

#include "lv_slider.h"
#include "../lv_obj/lv_group.h"
#include "../lv_draw/lv_draw.h"
#include "../lv_themes/lv_theme.h"
#include "../lv_misc/lv_math.h"

/*********************
 *      DEFINES
 *********************/
#define LV_SLIDER_SIZE_MIN      (4 << LV_ANTIALIAS)      /*hpad and vpad cannot make the bar or indicator smaller then this [px]*/
#define LV_SLIDER_NOT_PRESSED   INT16_MIN

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static bool lv_slider_design(lv_obj_t * slider, const lv_area_t * mask, lv_design_mode_t mode);
static lv_res_t lv_slider_signal(lv_obj_t * slider, lv_signal_t sign, void * param);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_design_func_t ancestor_design_f;
static lv_signal_func_t ancestor_signal;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a slider objects
 * @param par pointer to an object, it will be the parent of the new slider
 * @param copy pointer to a slider object, if not NULL then the new object will be copied from it
 * @return pointer to the created slider
 */
lv_obj_t * lv_slider_create(lv_obj_t * par, lv_obj_t * copy)
{
    /*Create the ancestor slider*/
    lv_obj_t * new_slider = lv_bar_create(par, copy);
    lv_mem_assert(new_slider);
    
    if(ancestor_design_f == NULL) ancestor_design_f = lv_obj_get_design_func(new_slider);
    if(ancestor_signal == NULL) ancestor_signal = lv_obj_get_signal_func(new_slider);

    /*Allocate the slider type specific extended data*/
    lv_slider_ext_t * ext = lv_obj_allocate_ext_attr(new_slider, sizeof(lv_slider_ext_t));
    lv_mem_assert(ext);

    /*Initialize the allocated 'ext' */
    ext->action = NULL;
    ext->drag_value = LV_SLIDER_NOT_PRESSED;
    ext->style_knob = &lv_style_pretty;
    ext->knob_in = 0;

    /*The signal and design functions are not copied so set them here*/
    lv_obj_set_signal_func(new_slider, lv_slider_signal);
    lv_obj_set_design_func(new_slider, lv_slider_design);

    /*Init the new slider slider*/
    if(copy == NULL) {
        lv_obj_set_click(new_slider, true);

        /*Set the default styles*/
        lv_theme_t *th = lv_theme_get_current();
        if(th) {
            lv_slider_set_style(new_slider, LV_SLIDER_STYLE_BG, th->slider.bg);
            lv_slider_set_style(new_slider, LV_SLIDER_STYLE_INDIC, th->slider.indic);
            lv_slider_set_style(new_slider, LV_SLIDER_STYLE_KNOB, th->slider.knob);
        } else {
            lv_slider_set_style(new_slider, LV_SLIDER_STYLE_KNOB, ext->style_knob);
        }
    }
    /*Copy an existing slider*/
    else {
    	lv_slider_ext_t * copy_ext = lv_obj_get_ext_attr(copy);
    	ext->style_knob = copy_ext->style_knob;
        ext->action = copy_ext->action;
        ext->knob_in = copy_ext->knob_in;
        /*Refresh the style with new signal function*/
        lv_obj_refresh_style(new_slider);
    }
    
    return new_slider;
}

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a function which will be called when a new value is set on the slider
 * @param slider pointer to slider object
 * @param action a callback function
 */
void lv_slider_set_action(lv_obj_t * slider, lv_action_t action)
{
    lv_slider_ext_t * ext = lv_obj_get_ext_attr(slider);
    ext->action = action;
}

/**
 * Set the 'knob in' attribute of a slider
 * @param slider pointer to slider object
 * @param in true: the knob is drawn always in the slider;
 *           false: the knob can be out on the edges
 */
void lv_slider_set_knob_in(lv_obj_t * slider, bool in)
{
    lv_slider_ext_t * ext = lv_obj_get_ext_attr(slider);
    ext->knob_in = in == false ? 0 : 1;
}

/**
 * Set a style of a slider
 * @param slider pointer to a slider object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_slider_set_style(lv_obj_t *slider, lv_slider_style_t type, lv_style_t *style)
{
    lv_slider_ext_t * ext = lv_obj_get_ext_attr(slider);

    switch (type) {
        case LV_SLIDER_STYLE_BG:
            lv_bar_set_style(slider, LV_BAR_STYLE_BG, style);
            break;
        case LV_SLIDER_STYLE_INDIC:
            lv_bar_set_style(slider, LV_BAR_STYLE_INDIC, style);
            break;
        case LV_SLIDER_STYLE_KNOB:
            ext->style_knob = style;
            lv_obj_refresh_ext_size(slider);
            break;
    }
}

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the slider action function
 * @param slider pointer to slider object
 * @return the callback function
 */
lv_action_t lv_slider_get_action(lv_obj_t * slider)
{
    lv_slider_ext_t * ext = lv_obj_get_ext_attr(slider);
    return ext->action;
}

/**
 * Set the styles of a slider
 * @param slider pointer to a slider object
 * @return pointer to the knob's style
 */
lv_style_t * lv_slider_get_style_knob(lv_obj_t * slider)
{
    lv_slider_ext_t * ext = lv_obj_get_ext_attr(slider);
    return ext->style_knob;

}

/**
 * Get the 'knob in' attribute of a slider
 * @param slider pointer to slider object
 * @return true: the knob is drawn always in the slider;
 *         false: the knob can be out on the edges
 */
bool lv_slider_get_knob_in(lv_obj_t * slider)
{
    lv_slider_ext_t * ext = lv_obj_get_ext_attr(slider);
    return ext->knob_in == 0 ? false : true;
}

/**
 * Get a style of a slider
 * @param slider pointer to a slider object
 * @param type which style should be get
 * @return style pointer to a style
 */
lv_style_t * lv_slider_get_style(lv_obj_t *slider, lv_slider_style_t type)
{
    lv_slider_ext_t *ext = lv_obj_get_ext_attr(slider);

    switch (type) {
        case LV_SLIDER_STYLE_BG:    return lv_bar_get_style(slider, LV_BAR_STYLE_BG);
        case LV_SLIDER_STYLE_INDIC: return lv_bar_get_style(slider, LV_BAR_STYLE_INDIC);
        case LV_SLIDER_STYLE_KNOB:  return ext->style_knob;
        default: return NULL;
    }

    /*To avoid warning*/
    return NULL;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


/**
 * Handle the drawing related tasks of the sliders
 * @param slider pointer to an object
 * @param mask the object will be drawn only in this area
 * @param mode LV_DESIGN_COVER_CHK: only check if the object fully covers the 'mask_p' area
 *                                  (return 'true' if yes)
 *             LV_DESIGN_DRAW: draw the object (always return 'true')
 *             LV_DESIGN_DRAW_POST: drawing after every children are drawn
 * @param return true/false, depends on 'mode'
 */
static bool lv_slider_design(lv_obj_t * slider, const lv_area_t * mask, lv_design_mode_t mode)
{
    /*Return false if the object is not covers the mask_p area*/
    if(mode == LV_DESIGN_COVER_CHK) {
    	return false;
    }
    /*Draw the object*/
    else if(mode == LV_DESIGN_DRAW_MAIN) {
        lv_slider_ext_t * ext = lv_obj_get_ext_attr(slider);

        lv_style_t * style_slider = lv_slider_get_style(slider, LV_SLIDER_STYLE_BG);
        lv_style_t * style_knob = lv_slider_get_style(slider, LV_SLIDER_STYLE_KNOB);
        lv_style_t * style_indic = lv_slider_get_style(slider, LV_SLIDER_STYLE_INDIC);

        /*Draw the bar*/
        lv_area_t area_bar;
        area_cpy(&area_bar, &slider->coords);
        /*Be sure at least vpad/hpad width bar will remain*/
       lv_coord_t pad_ver_bar = style_slider->body.padding.ver;
       lv_coord_t pad_hor_bar = style_slider->body.padding.hor;
       if(pad_ver_bar * 2 + LV_SLIDER_SIZE_MIN > area_get_height(&area_bar)) {
           pad_ver_bar = (area_get_height(&area_bar) - LV_SLIDER_SIZE_MIN) >> 1;
       }
       if(pad_hor_bar * 2 + LV_SLIDER_SIZE_MIN > area_get_width(&area_bar)) {
           pad_hor_bar = (area_get_width(&area_bar) - LV_SLIDER_SIZE_MIN) >> 1;
       }

        area_bar.x1 += pad_hor_bar;
        area_bar.x2 -= pad_hor_bar;
        area_bar.y1 += pad_ver_bar;
        area_bar.y2 -= pad_ver_bar;
        lv_draw_rect(&area_bar, mask, style_slider);

        /*Draw the indicator*/
        lv_area_t area_indic;
        area_cpy(&area_indic, &area_bar);

        /*Be sure at least vpad/hpad width indicator will remain*/
        lv_coord_t pad_ver_indic = style_indic->body.padding.ver;
        lv_coord_t pad_hor_indic = style_indic->body.padding.hor;
        if(pad_ver_indic * 2 + LV_SLIDER_SIZE_MIN > area_get_height(&area_bar)) {
            pad_ver_indic = (area_get_height(&area_bar) - LV_SLIDER_SIZE_MIN) >> 1;
        }
        if(pad_hor_indic * 2 + LV_SLIDER_SIZE_MIN > area_get_width(&area_bar)) {
            pad_hor_indic = (area_get_width(&area_bar) - LV_SLIDER_SIZE_MIN) >> 1;
        }

        area_indic.x1 += pad_hor_indic;
        area_indic.x2 -= pad_hor_indic;
        area_indic.y1 += pad_ver_indic;
        area_indic.y2 -= pad_ver_indic;

        lv_coord_t slider_w = area_get_width(&slider->coords);
        lv_coord_t slider_h = area_get_height(&slider->coords);

        lv_coord_t cur_value = lv_slider_get_value(slider);
        lv_coord_t min_value = lv_slider_get_min_value(slider);
        lv_coord_t max_value = lv_slider_get_max_value(slider);

        /*If dragged draw to the drag position*/
        if(ext->drag_value != LV_SLIDER_NOT_PRESSED) cur_value = ext->drag_value;

        if(slider_w >= slider_h) {
            area_indic.x2 = (int32_t) ((int32_t)area_get_width(&area_indic) * (cur_value - min_value)) / (max_value - min_value);
            area_indic.x2 += area_indic.x1;

        } else {
            area_indic.y1 = (int32_t) ((int32_t)area_get_height(&area_indic) * (cur_value - min_value)) / (max_value - min_value);
            area_indic.y1 = area_indic.y2 - area_indic.y1;
        }

        if(cur_value != min_value) lv_draw_rect(&area_indic, mask, style_indic);

        /*Draw the knob*/
        lv_area_t knob_area;
        area_cpy(&knob_area, &slider->coords);

        if(slider_w >= slider_h) {
            if(ext->knob_in == 0) {
                knob_area.x1 = area_indic.x2 - slider_h / 2;
                knob_area.x2 = knob_area.x1 + slider_h;
            } else {
                knob_area.x1 = (int32_t) ((int32_t)(slider_w - slider_h) * cur_value) / (max_value - min_value);
                knob_area.x1 += slider->coords.x1;
                knob_area.x2 = knob_area.x1 + slider_h;
            }

            knob_area.y1 = slider->coords.y1;
            knob_area.y2 = slider->coords.y2;
        } else {
            if(ext->knob_in == 0) {
                knob_area.y1 = area_indic.y1 - slider_w / 2;
                knob_area.y2 = knob_area.y1 + slider_w;
            } else {
                knob_area.y2 = (int32_t) ((int32_t)(slider_h - slider_w) * cur_value) / (max_value - min_value);
                knob_area.y2 = slider->coords.y2 - knob_area.y2;
                knob_area.y1 = knob_area.y2 - slider_w;
            }
            knob_area.x1 = slider->coords.x1;
            knob_area.x2 = slider->coords.x2;

        }

        lv_draw_rect(&knob_area, mask, style_knob);

    }
    /*Post draw when the children are drawn*/
    else if(mode == LV_DESIGN_DRAW_POST) {

    }

    return true;
}

/**
 * Signal function of the slider
 * @param slider pointer to a slider object
 * @param sign a signal type from lv_signal_t enum
 * @param param pointer to a signal specific variable
 * @return LV_RES_OK: the object is not deleted in the function; LV_RES_INV: the object is deleted
 */
static lv_res_t lv_slider_signal(lv_obj_t * slider, lv_signal_t sign, void * param)
{
    lv_res_t res;

    /* Include the ancient signal function */
    res = ancestor_signal(slider, sign, param);
    if(res != LV_RES_OK) return res;

    lv_slider_ext_t * ext = lv_obj_get_ext_attr(slider);
    lv_point_t p;
    lv_coord_t w = lv_obj_get_width(slider);
    lv_coord_t h = lv_obj_get_height(slider);

    if(sign == LV_SIGNAL_PRESSED) {
        ext->drag_value = lv_slider_get_value(slider);
    }
    else if(sign == LV_SIGNAL_PRESSING) {
        lv_indev_get_point(param, &p);
        if(w > h) {
            lv_coord_t knob_w = h;
            p.x -= slider->coords.x1 + h / 2;    /*Modify the point to shift with half knob (important on the start and end)*/
            ext->drag_value = (int32_t) ((int32_t) p.x * (ext->bar.max_value - ext->bar.min_value + 1)) / (w - knob_w);
            ext->drag_value += ext->bar.min_value;
        } else {
            lv_coord_t knob_h = w;
            p.y -= slider->coords.y1 + w / 2;    /*Modify the point to shift with half knob (important on the start and end)*/
            ext->drag_value = (int32_t) ((int32_t) p.y * (ext->bar.max_value - ext->bar.min_value + 1)) / (h - knob_h);
            ext->drag_value = ext->bar.max_value - ext->drag_value;     /*Invert the value: smaller value means higher y*/
        }

        if(ext->drag_value < ext->bar.min_value) ext->drag_value = ext->bar.min_value;
        else if(ext->drag_value > ext->bar.max_value) ext->drag_value = ext->bar.max_value;
        lv_obj_invalidate(slider);
    }
    else if (sign == LV_SIGNAL_PRESS_LOST) {
        ext->drag_value = LV_SLIDER_NOT_PRESSED;
        lv_obj_invalidate(slider);

    }
    else if (sign == LV_SIGNAL_RELEASED) {
        lv_slider_set_value(slider, ext->drag_value);
        ext->drag_value = LV_SLIDER_NOT_PRESSED;
        if(ext->action != NULL) ext->action(slider);
    }
    else if(sign == LV_SIGNAL_CORD_CHG) {
        /* The knob size depends on slider size.
         * During the drawing method the ext. size is used by the knob so refresh the ext. size.*/
        if(lv_obj_get_width(slider) != area_get_width(param) ||
          lv_obj_get_height(slider) != area_get_height(param)) {
            slider->signal_func(slider, LV_SIGNAL_REFR_EXT_SIZE, NULL);
        }
    } else if(sign == LV_SIGNAL_REFR_EXT_SIZE) {
        lv_style_t *style = lv_slider_get_style(slider, LV_SLIDER_STYLE_BG);
        lv_style_t *knob_style = lv_slider_get_style(slider, LV_SLIDER_STYLE_KNOB);
        lv_coord_t shadow_w = knob_style->body.shadow.width;
        if(ext->knob_in == 0) {
            lv_coord_t x = LV_MATH_MIN(w / 2 + shadow_w, h / 2 + shadow_w);      /*The smaller size is the knob diameter*/
            if(slider->ext_size < x) slider->ext_size = x;
        } else {
            lv_coord_t pad = LV_MATH_MIN(style->body.padding.hor, style->body.padding.ver);
            if(pad < 0) {
                pad = -pad;
                if(slider->ext_size < pad) slider->ext_size = pad;
            }
            if(slider->ext_size < shadow_w) slider->ext_size = shadow_w;
        }
    } else if(sign == LV_SIGNAL_CONTROLL) {
        lv_slider_ext_t * ext = lv_obj_get_ext_attr(slider);
        char c = *((char*)param);
        if(c == LV_GROUP_KEY_RIGHT || c == LV_GROUP_KEY_UP) {
            lv_slider_set_value(slider, lv_slider_get_value(slider) + 1);
            if(ext->action != NULL) ext->action(slider);
        } else if(c == LV_GROUP_KEY_LEFT || c == LV_GROUP_KEY_DOWN) {
            lv_slider_set_value(slider, lv_slider_get_value(slider) - 1);
            if(ext->action != NULL) ext->action(slider);
        }
    }

    return res;
}
#endif
