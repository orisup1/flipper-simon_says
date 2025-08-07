#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

// Constants
#define MAX_SEQUENCE_LENGTH 100

// Function declarations
void generate_sequence(int *sequence, int length);
int check_input(int *sequence, int *user_input, int length);
void update_score(int *score, int correct);

#endif // GAME_LOGIC_H