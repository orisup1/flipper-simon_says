#include <stdio.h>
#include <stdbool.h>

#ifdef DESKTOP
#include <unistd.h>
#endif

#include "game_logic.h"
#include "input.h"
#include "random.h"

#ifndef DESKTOP
#include <furi.h>
#endif

#define MAX_SEQUENCE_LENGTH 100

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
    display_message("Initializing Flipper Zero Game...");
#else
    display_message("Initializing Flipper Zero Game (Terminal Simulation)...");
#endif
}

void show_sequence(const int* sequence, int length) {
    for (int i = 0; i < length; i++) {
        char action_msg[64];
        snprintf(action_msg, sizeof(action_msg), "Press: %s", button_name(sequence[i]));
        display_message(action_msg);
        display_button_press(sequence[i]);
        sleep_ms(700);
    }
}

void game_loop() {
    int score = 0;
    int sequence[MAX_SEQUENCE_LENGTH];
    int user_input[MAX_SEQUENCE_LENGTH];
    int sequence_length = 1;

    while (true) {
        generate_sequence(sequence, sequence_length);
        show_sequence(sequence, sequence_length);

        get_user_input(user_input, sequence_length);

        if (check_input(user_input, sequence, sequence_length)) {
            score++;
            sequence_length++;
            char msg[64];
            snprintf(msg, sizeof(msg), "Correct! Score: %d", score);
            display_message(msg);
            sleep_ms(1000);
            if(sequence_length > MAX_SEQUENCE_LENGTH) {
                display_message("Max sequence length reached! You win!");
                break;
            }
        } else {
            char msg[64];
            snprintf(msg, sizeof(msg), "Wrong! Final Score: %d", score);
            display_message(msg);
            break;
        }
    }
}

#ifdef DESKTOP
int main() {
    initialize_game();
    game_loop();
    return 0;
}
#else
// Flipper app entry point matching application.fam
int32_t simonsays_main(void* p) {
    (void)p;
    initialize_game();
    game_loop();
    input_deinit();
    return 0;
}
#endif