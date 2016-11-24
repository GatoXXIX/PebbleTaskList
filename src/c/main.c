/* Author:        Gartenlehner Daniel */
/* Enrolment nr.: S1510307010         */
/* Exercise:      SWO32A04BB          */
/*                Pebble Projekt      */
/* Created on:    24.11.2016          */ 
/* Semester:      WS 16/17            */
/* FileName:      main.c              */

#include <pebble.h>
#include "tl_win_homescreen.h"

int main(void) {
  tl_win_homescreen_init();
  app_event_loop();
  tl_win_homescreen_destroy();
}
