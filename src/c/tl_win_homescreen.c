#include <pebble.h>
#include "tl_win_homescreen.h"
#include "tl_win_overview.h"

Window *homescreen_window;
TextLayer *homescreen_textlayer;

/* Event triggered on clicking 'SELECT' on homescreen */
void tl_win_homescreen_click_select_handler(ClickRecognizerRef recognizer, void *context) {
    tl_win_overview_init();
    tl_win_homescreen_destroy();    
}

/* Event triggered on clicking 'BACK' on homescreen */
void tl_win_homescreen_click_back_handler(ClickRecognizerRef recognizer, void *context) {
    window_stack_pop_all(true);
    tl_win_homescreen_destroy();
}

void tl_win_homescreen_init_handlers(Window *window) {    
    window_single_click_subscribe(BUTTON_ID_SELECT, tl_win_homescreen_click_select_handler);
    window_single_click_subscribe(BUTTON_ID_BACK, tl_win_homescreen_click_back_handler);
}

static void tl_win_homescreen_load(Window *window) {
    Layer *homescreen_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(homescreen_layer);
    homescreen_textlayer = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
    text_layer_set_text(homescreen_textlayer, "\n\nTaskList\nby\nS1510307010\n\nSELECT to CONTINUE\nBACK to QUIT");
    text_layer_set_text_alignment(homescreen_textlayer, GTextAlignmentCenter);
    layer_add_child(homescreen_layer, text_layer_get_layer(homescreen_textlayer));
}

void tl_win_homescreen_unload(Window *window) {
    text_layer_destroy(homescreen_textlayer);
}

void tl_win_homescreen_init() {
  homescreen_window = window_create();
  window_set_window_handlers(homescreen_window, (WindowHandlers) {
    .load = tl_win_homescreen_load,
    .unload = tl_win_homescreen_unload,
  });
  window_set_click_config_provider(homescreen_window, (ClickConfigProvider) tl_win_homescreen_init_handlers);
  window_stack_push(homescreen_window, true);
}

void tl_win_homescreen_destroy() {
  window_destroy(homescreen_window);
}