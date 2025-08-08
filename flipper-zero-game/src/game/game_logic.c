#include <stdio.h>
#include "game_logic.h"
#include "random.h"

void generate_sequence(int* sequence, int length) {
    if(sequence == NULL || length <= 0) {
        return;
    }
    for(int i = 0; i < length; i++) {
        sequence[i] = get_random_number(0, 3); // 0..3 representing UP, DOWN, LEFT, RIGHT
    }
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