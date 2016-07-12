#include "time_service.h"

/**
 * this method will fetch the 
 * local time and paste it on a given text layer
 */
TextLayer* update_time(TextLayer *text_layer){
    // Get an tim structure
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);
    
    // Write the current hours an minutes into the buffer
    static char s_buffer[8];
    strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
    
    // Display the time on the text layer
    text_layer_set_text(text_layer, s_buffer);
    
    return text_layer;
}

