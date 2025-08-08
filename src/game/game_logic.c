#include <stdio.h>
#include "game_logic.h"
#include "../utils/random.h"

void append_next_step(int* sequence, int index) {
    if(!sequence || index < 0 || index >= MAX_SEQUENCE_LENGTH) return;
    sequence[index] = get_random_number(0, 3);
}

int check_input(int* user_input, int* sequence, int length) {
    if(user_input == NULL || sequence == NULL || length <= 0) {
        return 0;
    }
    for(int i = 0; i < length; i++) {
        if(user_input[i] != sequence[i]) {
            return 0; // Incorrect
        }
    }
    return 1; // Correct
}