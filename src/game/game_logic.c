#include <stdio.h>
#include <stdbool.h>
#include "game_logic.h"
#include "../utils/random.h"

void append_next_step(ButtonCode* sequence, int index) {
    if(sequence == NULL || index < 0 || index >= MAX_SEQUENCE_LENGTH) return;

    ButtonCode next_button;
    if(index == 0) {
        next_button = (ButtonCode)get_random_number(0, 3);
    } else {
        ButtonCode previous_button = sequence[index - 1];
        do {
            next_button = (ButtonCode)get_random_number(0, 3);
        } while(next_button == previous_button);
    }
    sequence[index] = next_button;
}

bool check_input(const ButtonCode* user_input, const ButtonCode* sequence, int length) {
    if(user_input == NULL || sequence == NULL || length <= 0) {
        return false;
    }
    for(int i = 0; i < length; i++) {
        if(user_input[i] != sequence[i]) {
            return false; // Incorrect
        }
    }
    return true; // Correct
}