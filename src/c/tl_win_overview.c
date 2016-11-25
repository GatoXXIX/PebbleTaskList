/* Author:        Gartenlehner Daniel */
/* Enrolment nr.: S1510307010         */
/* Exercise:      SWO32A04BB          */
/*                Pebble Projekt      */
/* Created on:    24.11.2016          */ 
/* Semester:      WS 16/17            */
/* FileName:      tl_win_overview.c   */

#include <pebble.h>
#include <stdlib.h>
#include <stdio.h>
#include "tl_win_homescreen.h"
#include "tl_win_overview.h"
#include "tl_data.h"
#include "tl_win_creation.h"
#include "tl_win_view.h"

/* Defines */
#define MENU_CREATE_TASK "CREATE TASK"
#define MENU_VIEW_ALL "VIEW ALL TASKS"
#define MENU_VIEW_PRIO "VIEW BY PRIORITY"
#define MENU_VIEW_DATE "VIEW BY DATE"

/* Prototypes */
void tl_win_overview_select(int index, void *ctx);
void tl_win_overview_load(Window *window);
void tl_win_overview_unload(Window *window);
void createAutomatedSampleTaskData();

/* Variables */
Window *overview_window;
static SimpleMenuLayer *overview_simplemenulayer;
static SimpleMenuItem menu_items[4];
static SimpleMenuSection menu_sections[1];

/* Global methods defined in header */
void tl_win_overview_init() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_overview_init");
  overview_window = window_create();
  window_set_window_handlers(overview_window, (WindowHandlers) {
    .load = tl_win_overview_load,
    .unload = tl_win_overview_unload,
  });
  window_stack_push(overview_window, true); 
}

void tl_win_overview_destroy() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_overview_destroy");
  window_destroy(overview_window);
}

/* Implementations */
void tl_win_overview_select(int index, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "overview_click_select --> %d", index);
    
  if(index == 0)
    tl_win_creation_init(); /* Event -> Create task */
  else if (index == 1)
    tl_win_view_init_by_mode(0); /* Event -> View all tasks */
  else if (index == 2)
    tl_win_view_init_by_mode(1); /* Event -> View tasks ordered by priority */   
  else if (index == 3)
    tl_win_view_init_by_mode(2); /* Event -> View tasks ordered by priority */   
  else
    tl_win_view_init_by_mode(0);
  
  /* Destroy */
  tl_win_overview_destroy();    
}

void tl_win_overview_load(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_overview_load");
  
  menu_items[0] = (SimpleMenuItem) {
    .title = MENU_CREATE_TASK,
    .callback = tl_win_overview_select,
  };
  menu_items[1] = (SimpleMenuItem) {
    .title = MENU_VIEW_ALL,
    .callback = tl_win_overview_select,
  };
  menu_items[2] = (SimpleMenuItem) {
    .title = MENU_VIEW_PRIO,
    .callback = tl_win_overview_select,
  };
     menu_items[3] = (SimpleMenuItem) {
    .title = MENU_VIEW_DATE,
    .callback = tl_win_overview_select,
  };

  menu_sections[0] = (SimpleMenuSection) {
    .num_items = 4,
    .items = menu_items,
  };
    
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  overview_simplemenulayer = simple_menu_layer_create(bounds, window, menu_sections, 1, NULL);
  layer_add_child(window_layer, simple_menu_layer_get_layer(overview_simplemenulayer));
    
  /* Memory allocation causes to crash the pebble-app */
  /* Activate for documentation only */
  // createAutomatedSampleTaskData();  
}

void createAutomatedSampleTaskData() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_overview_init --> Pre createData");
  Data *d = createData();
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_overview_init --> Post createData");
  printData(d);  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_overview_init --> Post printData");
}

void tl_win_overview_unload(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_overview_unload");
  simple_menu_layer_destroy(overview_simplemenulayer);
}


