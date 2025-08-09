#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "input.h"

#ifndef DESKTOP
#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <gui/canvas.h>
#include <input/input.h>

// XBM assets (1-bit bitmaps) generated from PNGs
#include "../../assets/base.xbm"
#include "../../assets/base-up.xbm"
#include "../../assets/base-down.xbm"
#include "../../assets/base-left.xbm"
#include "../../assets/base-right.xbm"

static Gui* gui = NULL;
static ViewPort* viewport = NULL;
static FuriMessageQueue* input_queue = NULL;
static char draw_text_buf[48] = {0};

// Current image to draw (when set). When NULL, text buffer will be drawn instead
static const unsigned char* current_image_bits = NULL;
static int current_image_width = 0;
static int current_image_height = 0;

static void set_current_image(const unsigned char* bits, int width, int height) {
    current_image_bits = bits;
    current_image_width = width;
    current_image_height = height;
    if(viewport) view_port_update(viewport);
}

static void draw_callback(Canvas* canvas, void* context) {
    (void)context;
    canvas_clear(canvas);
    canvas_set_color(canvas, ColorBlack);
    if(current_image_bits != NULL && current_image_width > 0 && current_image_height > 0) {
        int x = (128 - current_image_width) / 2;
        int y = (64 - current_image_height) / 2;
        if(x < 0) x = 0;
        if(y < 0) y = 0;
        canvas_draw_xbm(canvas, x, y, current_image_width, current_image_height, current_image_bits);
    } else {
        canvas_set_font(canvas, FontSecondary);
        canvas_draw_str(canvas, 2, 12, draw_text_buf);
    }
}

static void input_callback(InputEvent* event, void* context) {
    FuriMessageQueue* queue = (FuriMessageQueue*)context;
    if(!queue || !event) return;
    furi_message_queue_put(queue, event, 0);
}

void input_init(void) {
    gui = furi_record_open(RECORD_GUI);
    viewport = view_port_alloc();
    input_queue = furi_message_queue_alloc(8, sizeof(InputEvent));
    view_port_draw_callback_set(viewport, draw_callback, NULL);
    view_port_input_callback_set(viewport, input_callback, input_queue);
    gui_add_view_port(gui, viewport, GuiLayerFullscreen);
    // Default to base image when there is no specific message
    set_current_image(base_bits, base_width, base_height);
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
    if(input_queue) {
        furi_message_queue_free(input_queue);
        input_queue = NULL;
    }
}

void display_clear(void) {
    draw_text_buf[0] = '\0';
    // After clearing, show base image
    set_current_image(base_bits, base_width, base_height);
}

void input_flush_events(void) {
    if(!input_queue) return;
    InputEvent ev;
    while(furi_message_queue_get(input_queue, &ev, 0) == FuriStatusOk) {
        // discard
    }
}

static void set_draw_text(const char* text) {
    if(text == NULL) text = "";
    size_t i = 0;
    for(; i < sizeof(draw_text_buf) - 1 && text[i] != '\0'; i++) {
        draw_text_buf[i] = text[i];
    }
    draw_text_buf[i] = '\0';
    // When text is set, prefer rendering text (disable image)
    current_image_bits = NULL;
    current_image_width = 0;
    current_image_height = 0;
    if(viewport) view_port_update(viewport);
}

static int map_key_to_code(InputKey key) {
    switch(key) {
        case InputKeyUp: return 0;
        case InputKeyDown: return 1;
        case InputKeyLeft: return 2;
        case InputKeyRight: return 3;
        case InputKeyOk: return 4;
        case InputKeyBack: return 5;
        default: return -1;
    }
}

static int read_button_press_strict(void) {
    InputEvent ev;
    // Wait for a press/short
    while(true) {
        if(furi_message_queue_get(input_queue, &ev, FuriWaitForever) != FuriStatusOk) continue;
        if(ev.type == InputTypePress || ev.type == InputTypeShort) {
            int code = map_key_to_code(ev.key);
            if(code == -1) continue;
            // Now wait for release of that same key to avoid repeats
            InputKey released_key = ev.key;
            while(true) {
                if(furi_message_queue_get(input_queue, &ev, FuriWaitForever) != FuriStatusOk) continue;
                if(ev.type == InputTypeRelease && ev.key == released_key) break;
                // Ignore other noise (Repeat/Long/other keys) until release of this key
            }
            return code;
        }
        // Ignore Repeat/Long/Release and any other events
    }
}

int wait_for_ok_or_back(void) {
    input_flush_events();
    set_draw_text("Simon Says\nOK: Start  Back: Exit");
    while(true) {
        int b = read_button_press_strict();
        if(b == 4) return 1;
        if(b == 5) return 0;
    }
}

#else

void input_init(void) {}
void input_deinit(void) {}
void input_flush_events(void) {}
void display_clear(void) { printf("\n"); }

static int clamp_button(int value) {
    if(value < 0) return 0;
    if(value > 3) return 3;
    return value;
}

int wait_for_ok_or_back(void) {
    printf("Simon Says - Press ENTER to start, or type 'q' to quit.\n");
    while(1) {
        int ch = getchar();
        if(ch == 'q' || ch == 'Q') return 0;
        if(ch == '\n') return 1;
    }
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
    switch(button) {
        case 0: // UP
            set_current_image(up_bits, up_width, up_height);
            break;
        case 1: // DOWN
            set_current_image(down_bits, down_width, down_height);
            break;
        case 2: // LEFT
            set_current_image(left_bits, left_width, left_height);
            break;
        case 3: // RIGHT
            set_current_image(right_bits, right_width, right_height);
            break;
        default:
            set_current_image(base_bits, base_width, base_height);
            break;
    }
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

int get_user_input(int* user_input, int length) {
    if(user_input == NULL || length <= 0) return 0;

#ifndef DESKTOP
    input_flush_events();
    for(int i = 0; i < length; i++) {
        int code = read_button_press_strict();
        if(code == 5) { // Back - ignore during input
            i--;
            continue;
        }
        if(code == 4) { // OK - ignore as input
            i--;
            continue;
        }
        if(code >= 0 && code <= 3) {
            user_input[i] = code;
            display_button_press(code);
        }
    }
    return 1;
#else
    for(int i = 0; i < length; i++) {
        while(1) {
            printf("Enter button %d of %d (0=UP,1=DOWN,2=LEFT,3=RIGHT, 9=Back to quit): ", i + 1, length);
            fflush(stdout);
            int value = read_int_from_stdin();
            if(value == 9) return 0;
            if(value >= 0 && value <= 3) {
                user_input[i] = value;
                break;
            }
            printf("Invalid input. Please enter a number 0-3 or 9 to quit.\n");
        }
    }
    return 1;
#endif
}