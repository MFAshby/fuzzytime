#include <pebble.h>
#include "fuzz.h"
#include "main.h"

#ifdef DEBUG
#include "tests.h"
#endif

static Window* the_window;
static TextLayer* the_text_layer;
static char the_time[MAX_TIME_LEN];

void on_tick(struct tm* tick_time, TimeUnits units_changed) {
  fuzzy_time(the_time, MAX_TIME_LEN, tick_time->tm_min, tick_time->tm_hour);
  text_layer_set_text(the_text_layer, the_time);
}

void init() {
  the_window = window_create();
  window_stack_push(the_window, true);
  Layer* root_layer =  window_get_root_layer(the_window);
  GRect root_bounds = layer_get_bounds(root_layer);
  the_text_layer = text_layer_create(root_bounds);
  text_layer_set_text(the_text_layer, "");
  text_layer_set_font(the_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(the_text_layer, GTextAlignmentCenter);
  Layer* layer = text_layer_get_layer(the_text_layer);
  layer_add_child(root_layer, layer);
  
  tick_timer_service_subscribe(MINUTE_UNIT, on_tick);
}

void deinit() {
  text_layer_destroy(the_text_layer);
  window_destroy(the_window);
  tick_timer_service_unsubscribe();
}

int main(void) {
  if (DEBUG)
    run_tests();
  
  init();
  app_event_loop();
  deinit();
}