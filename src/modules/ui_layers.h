#pragma once
#include <pebble.h>

/**
 * creates the background layer and image
 */
BitmapLayer* create_background(Layer *main_layer );

/**
 * destroys the background if exists
 */
void destroy_background();

/**
 * creates the time layer and text
 */
TextLayer* create_time_display(Layer *main_layer);

/**
 * destroys the time display if exists
 */
void destroy_time_display();

