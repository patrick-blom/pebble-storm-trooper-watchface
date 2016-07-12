#include "main_window.h"
#include "modules/time_service.h"
#include "modules/ui_layers.h"

static Window *s_main_window;
static TextLayer *s_time_layer;

/**
 * this method creates the background and the time display
 * with custom font and push them to the main window
 */
static void main_window_load(Window *window){
    
    Layer *window_layer = window_get_root_layer(window);
    
    BitmapLayer *background_layer = create_background(window_layer);
    layer_add_child(window_layer, bitmap_layer_get_layer(background_layer));
    
    s_time_layer = create_time_display(window_layer);
    s_time_layer = update_time(s_time_layer);
    
    layer_add_child(window_layer,text_layer_get_layer(s_time_layer));
}

/**
 * this method will unload the time display and background
 */
static void main_window_unload(Window *window){
    
    destroy_time_display();
    destroy_background();
}

/**
 * this mehtod will be called if the tick time service sends a tick
 *
 * (TODO) move this some ware else
 */
static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
    s_time_layer = update_time(s_time_layer);
}

/**
 * this method registers the tick time callback and create
 * the main window if it not exist
 */
void main_window_push(){
    
    // Subcribe to the time sevice
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
    
    if(!s_main_window){
        s_main_window = window_create();
        window_set_window_handlers(s_main_window,(WindowHandlers){
            .load = main_window_load,
            .unload = main_window_unload
        });
        
        window_stack_push(s_main_window,true);
    }
}

/**
 * this method destroys the main window and frees memory
 */
void main_window_destroy(){
    if(s_main_window){
        window_destroy(s_main_window);
    }
}
