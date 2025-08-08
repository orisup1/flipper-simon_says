#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "input.h"

#ifndef DESKTOP
#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>

static Gui* gui = NULL;
static ViewPort* viewport = NULL;
static char draw_text_buf[64] = {0};

static void draw_callback(Canvas* canvas, void* context) {
    (void)context;
    canvas_clear(canvas);
    canvas_set_color(canvas, ColorBlack);
    canvas_draw_str(canvas, 2, 12, draw_text_buf);
}

static void input_callback(InputEvent* event, void* context) {
    (void)context;
    (void)event;
}

void input_init(void) {
    gui = furi_record_open(RECORD_GUI);
    viewport = view_port_alloc();
    view_port_draw_callback_set(viewport, draw_callback, NULL);
    view_port_input_callback_set(viewport, input_callback, NULL);
    gui_add_view_port(gui, viewport, GuiLayerFullscreen);
}

void input_deinit(void) {
    if(gui && viewport) {
        gui_remove_view_port(gui, viewport);
    }
    if(viewport) {
        view_port_free(viewport);
        viewport = NULL;
    }
    if(gui) {
        furi_record_close(RECORD_GUI);
        gui = NULL;
    }
}

static void set_draw_text(const char* text) {
    if(text == NULL) text = "";
    // Copy into persistent buffer
    size_t i = 0;
    for(; i < sizeof(draw_text_buf) - 1 && text[i] != '\0'; i++) {
        draw_text_buf[i] = text[i];
    }
    draw_text_buf[i] = '\0';
    if(viewport) {
        view_port_update(viewport);
    }
}

static int read_button_press_hal(void) {
    while(true) {
        if(furi_hal_gpio_read(&gpio_btn_up)) return 0;
        if(furi_hal_gpio_read(&gpio_btn_down)) return 1;
        if(furi_hal_gpio_read(&gpio_btn_left)) return 2;
        if(furi_hal_gpio_read(&gpio_btn_right)) return 3;
        furi_delay_ms(10);
    }
}
#else

void input_init(void) {}
void input_deinit(void) {}

static int clamp_button(int value) {
    if(value < 0) return 0;
    if(value > 3) return 3;
    return value;
}
#endif

const char* button_name(int button) {
#ifndef DESKTOP
    switch(button) {
        case 0: return "UP";
        case 1: return "DOWN";
        case 2: return "LEFT";
        case 3: return "RIGHT";
        default: return "?";
    }
#else
    switch(clamp_button(button)) {
        case 0: return "UP";
        case 1: return "DOWN";
        case 2: return "LEFT";
        case 3: return "RIGHT";
        default: return "?";
    }
#endif
}

void display_message(const char* message) {
#ifndef DESKTOP
    set_draw_text(message);
#else
    if(message) {
        printf("%s\n", message);
        fflush(stdout);
    }
#endif
}

void display_button_press(int button) {
#ifndef DESKTOP
    set_draw_text(button_name(button));
#else
    printf("[ %s ]\n", button_name(button));
    fflush(stdout);
#endif
}

#ifdef DESKTOP
static int read_int_from_stdin(void) {
    int value = -1;
    int result = scanf("%d", &value);
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF) {}
    if(result != 1) {
        return -1;
    }
    return value;
}
#endif

void get_user_input(int* user_input, int length) {
    if(user_input == NULL || length <= 0) return;

#ifndef DESKTOP
    for(int i = 0; i < length; i++) {
        int value = read_button_press_hal();
        user_input[i] = value;
        display_button_press(value);
        furi_delay_ms(150);
        while(furi_hal_gpio_read(&gpio_btn_up) || furi_hal_gpio_read(&gpio_btn_down) ||
              furi_hal_gpio_read(&gpio_btn_left) || furi_hal_gpio_read(&gpio_btn_right)) {
            furi_delay_ms(10);
        }
    }
#else
    for(int i = 0; i < length; i++) {
        while(1) {
            printf("Enter button %d of %d (0=UP,1=DOWN,2=LEFT,3=RIGHT): ", i + 1, length);
            fflush(stdout);
            int value = read_int_from_stdin();
            if(value >= 0 && value <= 3) {
                user_input[i] = value;
                break;
            }
            printf("Invalid input. Please enter a number 0-3.\n");
        }
    }
#endif
}