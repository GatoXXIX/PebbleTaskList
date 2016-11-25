#include <pebble.h>
#include <stdlib.h>
#include <stdio.h>
#include "tl_win_homescreen.h"
#include "tl_win_overview.h"
#include "tl_data.h"
#include "tl_win_creation.h"
#include "tl_win_view.h"

#define MENU_ITEMS 4
#define MENU_SECTIONS 1

Window *overview_window;
static SimpleMenuLayer *overview_simplemenulayer;

static SimpleMenuItem menu_items[MENU_ITEMS];
static SimpleMenuSection menu_sections[MENU_SECTIONS];

static void overview_click_select(int index, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "overview_click_select --> %d", index);
    switch(index) {
        case 0: 
            /* Event -> Create task */
            tl_win_creation_init();
            break;
        case 1:
            /* Event -> View all tasks */
            tl_win_view_init_by_mode(0);
            break;
        case 2:
            /* Event -> View tasks ordered by priority */ 
            tl_win_view_init_by_mode(1);
            break;
        case 3:
            /* Event > View tasks ordered by date */
            tl_win_view_init_by_mode(2);
            break;
        default:
            tl_win_view_init_by_mode(0);
            break;
    }
    tl_win_overview_destroy();    
}

static void tl_win_overview_load(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tl_win_overview_load");
  int num_a_items = 0;        
  menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "CREATE TASK",
    .callback = overview_click_select,
  };
  menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "VIEW ALL TASKS",
    .callback = overview_click_select,
  };
  menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "VIEW BY PRIORITY",
    .callback = overview_click_select,
  };
     menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "VIEW BY DATE",
    .callback = overview_click_select,
  };

    menu_sections[0] = (SimpleMenuSection) {
        .num_items = MENU_ITEMS,
        .items = menu_items,
    };
    
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  overview_simplemenulayer = simple_menu_layer_create(bounds, window, menu_sections, MENU_SECTIONS, NULL);
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
