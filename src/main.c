#include <stdio.h>
#include <stdbool.h>

#ifdef DESKTOP
#include <unistd.h>
#endif

#include "game/game_logic.h"
#include "game/input.h"
#include "utils/random.h"

#ifndef DESKTOP
#include <furi.h>
#endif

static ButtonCode g_sequence[MAX_SEQUENCE_LENGTH];
static ButtonCode g_user_input[MAX_SEQUENCE_LENGTH];

static void sleep_ms(int ms) {
#ifndef DESKTOP
    if(ms > 0) furi_delay_ms((uint32_t)ms);
#else
    if(ms <= 0) return;
    usleep((useconds_t)ms * 1000);
#endif
}

void initialize_game() {
    init_random();
#ifndef DESKTOP
    input_init();
    display_message("Simon Says\nOK: Start  Back: Exit");
#else
    display_message("Initializing Flipper Zero Game (Terminal Simulation)...");
#endif
}

void show_sequence(const ButtonCode* sequence, int length) {
    for (int i = 0; i < length; i++) {
        char action_msg[64];
        snprintf(action_msg, sizeof(action_msg), "Press: %s", button_name(sequence[i]));
        display_message(action_msg);
        display_button_press(sequence[i]);
        sleep_ms(600);
    }
}

static void run_rounds(void) {
    int score = 0;
    int sequence_length = 0;

    append_next_step(g_sequence, sequence_length);
    sequence_length = 1;

    while (true) {
        show_sequence(g_sequence, sequence_length);
        // Clear screen after sequence
        display_clear();
        sleep_ms(150);
        input_flush_events();

        if(!get_user_input(g_user_input, sequence_length)) {
            continue;
        }

        if (check_input(g_user_input, g_sequence, sequence_length)) {
            score++;
            char msg[64];
            snprintf(msg, sizeof(msg), "Correct! Score: %d", score);
            display_message(msg);
            sleep_ms(500);
            if(sequence_length >= MAX_SEQUENCE_LENGTH) {
                display_message("Max sequence length reached! You win!");
                break;
            }
            append_next_step(g_sequence, sequence_length);
            sequence_length++;
        } else {
            char msg[64];
            snprintf(msg, sizeof(msg), "Wrong! Final Score: %d", score);
            display_message(msg);
            sleep_ms(1200);
            break;
        }
    }
}

void game_loop() {
    while(true) {
        if(!wait_for_ok_or_back()) {
            return; // Back: exit app
        }
        run_rounds();
        // After finishing, return to menu
        display_message("Simon Says\nOK: Start  Back: Exit");
    }
}

#ifdef DESKTOP
int main() {
    initialize_game();
    game_loop();
    return 0;
}
#else
int32_t simonsays_main(void* p) {
    (void)p;
    initialize_game();
    game_loop();
    input_deinit();
    return 0;
}
#endif