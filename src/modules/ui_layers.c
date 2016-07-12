#include "ui_layers.h"

static BitmapLayer *s_background_layer;
static GBitmap *s_backgroud_bitmap;
static TextLayer *s_time_layer;
static GFont s_time_font;

/**
 * this method will create an background layer based 
 * on the main window and paste an bitmap on it
 */
BitmapLayer* create_background(Layer *main_layer){
    
    GRect bounds = layer_get_bounds(main_layer);

    s_backgroud_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
    s_background_layer = bitmap_layer_create(bounds);

    // APP_LOG(APP_LOG_LEVEL_DEBUG, "with: %d height: %d", bounds.size.w, bounds.size.h);
    bitmap_layer_set_bitmap(s_background_layer, s_backgroud_bitmap);
    
    return s_background_layer;
}

/**
 * this method will destroy the background layer and
 * the bitmap which's placed on it
 */
void destroy_background(){
    
    if(s_backgroud_bitmap){
        gbitmap_destroy(s_backgroud_bitmap);
    }
    
    if(s_background_layer){
        bitmap_layer_destroy(s_background_layer);
    }
}

/**
 * this method will create a text layer based on the window bounds
 * and set a custom background color and font
 */
TextLayer* create_time_display(Layer *main_layer){
    
    GRect bounds = layer_get_bounds(main_layer);
    
    s_time_layer = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(38,32),bounds.size.w,50));
    text_layer_set_background_color(s_time_layer, GColorClear);
    text_layer_set_text_color(s_time_layer,GColorBlack);
    
    s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_START_JEDI_20));
    
    text_layer_set_font(s_time_layer,s_time_font);
    text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
    
    return s_time_layer;
}

/**
 * this method will destroy the time layer and
 * unload the custom font
 */
void destroy_time_display(){
    
    if(s_time_layer){
        text_layer_destroy(s_time_layer);
    }
    
    if(s_time_font){
        fonts_load_custom_font(s_time_font);
    }
}
