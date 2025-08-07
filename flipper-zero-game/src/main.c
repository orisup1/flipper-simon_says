#include <stdio.h>
#include <stdlib.h>
#include "game/game_logic.h"
#include "game/input.h"

#define MAX_SEQUENCE_LENGTH 100

void initialize_game() {
    display_message("Initializing Flipper Zero Game...");
}

void show_sequence(const int* sequence, int length) {
    for (int i = 0; i < length; i++) {
        char action_msg[32];
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
            char msg[32];
            snprintf(msg, sizeof(msg), "Correct! Score: %d", score);
            display_message(msg);
            sleep_ms(1000);
        } else {
            char msg[32];
            snprintf(msg, sizeof(msg), "Wrong! Final Score: %d", score);
            display_message(msg);
            break;
        }
    }
}

int main() {
    initialize_game();
    game_loop();
    return 0;
}