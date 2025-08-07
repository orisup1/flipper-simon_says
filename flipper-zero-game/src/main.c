#include <stdio.h>
#include <stdlib.h>
#include "game/game_logic.h"
#include "game/input.h"

#define MAX_SEQUENCE_LENGTH 100

void initialize_game() {
    // Initialize game settings, display, etc.
    printf("Initializing Flipper Zero Game...\n");
}

void game_loop() {
    int score = 0;
    int sequence[MAX_SEQUENCE_LENGTH];
    int sequence_length = 1;

    while (true) {
        // Generate a new sequence
        generate_sequence(sequence, sequence_length);
        
        // Display the sequence to the user
        for (int i = 0; i < sequence_length; i++) {
            display_button_press(sequence[i]);
        }

        // Get user input
        if (check_input(sequence, sequence_length)) {
            score++;
            sequence_length++; // Increase the length of the sequence
            printf("Correct! Score: %d\n", score);
        } else {
            printf("Wrong! Final Score: %d\n", score);
            break; // End the game on wrong input
        }
    }
}

int main() {
    initialize_game();
    game_loop();
    return 0;
}