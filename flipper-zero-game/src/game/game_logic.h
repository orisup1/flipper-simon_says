#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define MAX_SEQUENCE_LENGTH 100

// Append a single random step at the given index (0-based)
void append_next_step(int* sequence, int index);

// Compare user input to the sequence prefix of given length
int check_input(int* user_input, int* sequence, int length);

#endif // GAME_LOGIC_H