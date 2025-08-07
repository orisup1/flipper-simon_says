#include "input.h"
#include <furi_hal.h> // Flipper Zero HAL for button input

// Map Flipper buttons to your game button indices
int read_button_press() {
    while (true) {
        if(furi_hal_gpio_read(&gpio_btn_up)) return 0;    // UP
        if(furi_hal_gpio_read(&gpio_btn_down)) return 1;  // DOWN
        if(furi_hal_gpio_read(&gpio_btn_left)) return 2;  // LEFT
        if(furi_hal_gpio_read(&gpio_btn_right)) return 3; // RIGHT
        furi_delay_ms(10); // Polling delay
    }
}

// Reads a sequence of button presses from the user
void get_user_input(int* user_input, int length) {
    for(int i = 0; i < length; i++) {
        user_input[i] = read_button_press();
        // Optional: add feedback or delay here
    }
}