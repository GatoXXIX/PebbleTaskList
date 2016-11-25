/* Author:        Gartenlehner Daniel */
/* Enrolment nr.: S1510307010         */
/* Exercise:      SWO32A04BB          */
/*                Pebble Projekt      */
/* Created on:    24.11.2016          */ 
/* Semester:      WS 16/17            */
/* FileName:      tl_win_view.c       */


#include <pebble.h>
#include "tl_win_view.h"
#include "tl_win_overview.h"

/* Prototypes */
void tl_win_view_click_back_handler(ClickRecognizerRef recognizer, void *context);
void tl_win_view_click_handler(Window *window);
void tl_win_view_init(); 
void tl_win_view_destroy();
void tl_win_view_load(Window *window);
void tl_win_view_unload(Window *window);
  
/* Variables */
Window *view_window;
TextLayer *view_textlayer;
int viewMode = 0;

/* Global methods defined in header */
void tl_win_view_init_by_mode(int mode) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_view_init_by_mode");
    viewMode = mode;
    tl_win_view_init();
}

/* Implementations */
void tl_win_view_click_back_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_view_click_back_handler");
    window_stack_pop_all(true);
    tl_win_overview_init();
    tl_win_view_destroy();
}

void tl_win_view_click_handler(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_view_click_handler");
    window_single_click_subscribe(BUTTON_ID_BACK, tl_win_view_click_back_handler);
}

void tl_win_view_init() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_view_init");
  view_window = window_create();
  window_set_window_handlers(view_window, (WindowHandlers) {
    .load = tl_win_view_load,
    .unload = tl_win_view_unload,
  });
  window_set_click_config_provider(view_window, (ClickConfigProvider) tl_win_view_click_handler);
  window_stack_push(view_window, true);
}

void tl_win_view_load(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_view_load");
    Layer *view_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(view_layer);
    view_textlayer = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  
  if(viewMode == 0) 
      text_layer_set_text(view_textlayer, "CURRENT VIEW: ALL\n------------\n");
  else if(viewMode == 1) 
      text_layer_set_text(view_textlayer, "CURRENT VIEW: PRIO\n-------------\n");
  else if(viewMode == 2) 
      text_layer_set_text(view_textlayer, "CURRENT VIEW: DATE\n-------------\n");
  
  text_layer_set_text_alignment(view_textlayer, GTextAlignmentCenter);
    layer_add_child(view_layer, text_layer_get_layer(view_textlayer));
}

void tl_win_view_unload(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_view_unload");
    text_layer_destroy(view_textlayer);
}

void tl_win_view_destroy() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_view_destroy");
  window_destroy(view_window);
}