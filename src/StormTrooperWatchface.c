#include <pebble.h>

static Window *s_main_window;

static TextLayer *s_time_layer;

static GFont s_time_font;

static BitmapLayer *s_background_layer;

static GBitmap *s_backgroud_bitmap;

static void update_time(){
    // Get an tim structure
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);
    
    // Write the current hours an minutes into the buffer
    static char s_buffer[8];
    strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
    
    // Display the time on the text layer
    text_layer_set_text(s_time_layer, s_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
    update_time();
}

static void main_window_load(Window *window){
    // Get information about the root layer
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
    
    // Creating Bitmap
    s_backgroud_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
    
    // Create Backgroundlayer which holds the Bitmap
    s_background_layer = bitmap_layer_create(bounds);

    // APP_LOG(APP_LOG_LEVEL_DEBUG, "with: %d height: %d", bounds.size.w, bounds.size.h);
    
    // Set the Bitmap on the Layer
    bitmap_layer_set_bitmap(s_background_layer, s_backgroud_bitmap);
    
    // Add the Bitmaplayer before the Textlayer
    layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
    
    // create the time layer with specific bounds
    s_time_layer = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(38,32),bounds.size.w,50));
    
    // set the time
    update_time();
    
    // Improve the text layer
    text_layer_set_background_color(s_time_layer, GColorClear);
    text_layer_set_text_color(s_time_layer,GColorBlack);
    
    // load custom font
    s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_START_JEDI_20));

    
    text_layer_set_font(s_time_layer,s_time_font);
    text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
    
    // Add time layer as child layer to the root layer of the window
    layer_add_child(window_layer,text_layer_get_layer(s_time_layer));
}

static void main_window_unload(Window *window){
    // Destroy the time layer
    text_layer_destroy(s_time_layer);
    
    // Destroy the custom font
    fonts_unload_custom_font(s_time_font);
    
    // Destroy the Bitmap
    gbitmap_destroy(s_backgroud_bitmap);
    
    // Destroy the Bitmaplayer
    bitmap_layer_destroy(s_background_layer);
}

static void init(){
    // Subcribe to the time sevice
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
    
    // Create the main window element
    s_main_window = window_create();
    
    // set handlers to manage the elements inside the window
    window_set_window_handlers(s_main_window,(WindowHandlers){
        .load = main_window_load,
        .unload = main_window_unload
    });
    
    // push the window
    window_stack_push(s_main_window,true);
}


static void deinit(){
    //Destroy window
    window_destroy(s_main_window);
}

int main(void) {
    init();
    app_event_loop();
    deinit();
}
