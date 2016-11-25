/* Author:        Gartenlehner Daniel */
/* Enrolment nr.: S1510307010         */
/* Exercise:      SWO32A04BB          */
/*                Pebble Projekt      */
/* Created on:    24.11.2016          */ 
/* Semester:      WS 16/17            */
/* FileName:      tl_win_creation.c   */

#include <pebble.h>
#include "tl_win_creation.h"
#include "tl_win_overview.h"

/* Internal Prototypes */
static void tl_win_creation_load(Window *window);
void tl_win_creation_unload(Window *window);

/* Variables */
Window *creation_window;
TextLayer *creation_textlayer;

/* Global methods defined in header */
void tl_win_creation_init() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_creation_init");
  creation_window = window_create();
  window_set_window_handlers(creation_window, (WindowHandlers) {
    .load = tl_win_creation_load,
    .unload = tl_win_creation_unload,
  });
  window_stack_push(creation_window, true);
  
  /* Auto creat logic with memory allocation kills pebble watch */
  /* Showing text only */
  
  app_timer_register(3000, tl_win_overview_init, NULL);
  tl_win_creation_destroy();
}

void tl_win_creation_destroy() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_creation_destroy");
  window_destroy(creation_window);
}

/* Implementations */
void tl_win_creation_load(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_creation_load");
  Layer *creation_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(creation_layer);
  creation_textlayer = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  text_layer_set_text(creation_textlayer, "\n\nTask will be\nautomatically created now!\nPlease wait.\n\n");
  text_layer_set_text_alignment(creation_textlayer, GTextAlignmentCenter);
  layer_add_child(creation_layer, text_layer_get_layer(creation_textlayer));
}

void tl_win_creation_unload(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_creation_unload");
  text_layer_destroy(creation_textlayer);
}

