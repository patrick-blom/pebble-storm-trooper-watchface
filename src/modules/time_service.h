#pragma once
#include <pebble.h>

/**
 * this method updates the text layer and is called 
 * ervery time the tick time services sents a tick
 */
TextLayer* update_time(TextLayer *text_layer);
