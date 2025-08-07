#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_logic.h"

#define MAX_SEQUENCE_LENGTH 100

static int sequence[MAX_SEQUENCE_LENGTH];
static int current_length = 0;
static int score = 0;

void generate_sequence() {
    current_length++;
    if (current_length > MAX_SEQUENCE_LENGTH) {
        current_length = MAX_SEQUENCE_LENGTH;
    }
    sequence[current_length - 1] = get_random_number(0, 3); // Assuming 4 buttons (0-3)
}

int check_input(int user_input[], int length) {
    for (int i = 0; i < length; i++) {
        if (user_input[i] != sequence[i]) {
            return 0; // Incorrect input
        }
    }
    return 1; // Correct input
}

void update_score() {
    score++;
}

int get_score() {
    return score;
}

void reset_game() {
    current_length = 0;
    score = 0;
}