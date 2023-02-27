#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>

#include "conf.h"
#include "tbgui_parts.h"
#include "app_state.h"
#include "window_main.h"

static void text_area_cb(lv_obj_t * obj, lv_event_t event);

window_t* tbgui_main_window_init(void)
{
	window_t* window = create_window("Hello GUI");

	lv_obj_t * description_label = lv_label_create(window->main_container, NULL);
	lv_label_set_long_mode(description_label, LV_LABEL_LONG_BREAK);
	lv_obj_set_width(description_label, lv_obj_get_width_fit(window->main_container));
	lv_label_set_text(
		description_label,
		"Hello!\n\nHopefully this works!"
	);

	// Add a passphrase input (WIP)
	lv_obj_t * text_area = lv_ta_create(window->main_container, NULL);
	lv_ta_set_one_line(text_area, true);
	lv_ta_set_text(text_area, "");
	lv_ta_set_placeholder_text(text_area, "Passphrase??");
	lv_ta_set_pwd_mode(text_area, true);
	lv_ta_set_pwd_show_time(text_area, 0);
	lv_obj_set_width(text_area, lv_obj_get_width_fit(window->main_container) - 10 /* ?? */);
	lv_obj_set_event_cb(text_area, text_area_cb);

	// Add the keyboard
	lv_obj_t * parent = lv_layer_top();
	lv_obj_t * keyboard = lv_kb_create(parent, NULL);
	lv_obj_set_protect(keyboard, LV_PROTECT_POS);
	lv_obj_set_width(keyboard, lv_obj_get_width(parent));
	lv_obj_set_height(keyboard, lv_obj_get_height(parent) / 2);
	lv_obj_set_x(keyboard, 0);
	lv_obj_set_y(keyboard, lv_obj_get_height(parent) / 2);
	lv_kb_set_ta(keyboard, text_area);

	//lv_page_focus(window->main_container, text_area, false);
	lv_group_focus_obj(text_area);

	// Buttons

	/*
	add_button(
		window->actions_container,
		APP_ACTION_QUIT,
		"Quit"
	);
	*/

	finalize_window(window);

	app->main_window = window;

	return window;
}

static void text_area_cb(lv_obj_t * obj, lv_event_t event)
{
    switch(event) {
		case LV_EVENT_INSERT:
			{
				char * inserted = lv_event_get_data();
				//printf("INSERT: %s\n", inserted);
				if (inserted[0] == '\n') {
					printf("-> '%s'\n", lv_ta_get_text(obj));
					app->action = APP_ACTION_QUIT; // XXX SUBMIT
				}
			}
			break;

        case LV_EVENT_APPLY:
        case LV_EVENT_VALUE_CHANGED:
        case LV_EVENT_CLICKED:
        case LV_EVENT_LONG_PRESSED:
        case LV_EVENT_LONG_PRESSED_REPEAT:
        case LV_EVENT_PRESSED:
        case LV_EVENT_RELEASED:
        case LV_EVENT_SHORT_CLICKED:
			break;

		default:
#if 0
            printf("Unhandled event: %d;\n", (int)event);
#endif
			break;
    }
}
