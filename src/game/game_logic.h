#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>
#include "input.h"

#define MAX_SEQUENCE_LENGTH 100

// Append a single random directional step at the given index (0-based)
void append_next_step(ButtonCode* sequence, int index);

// Compare user input to the sequence prefix of given length
bool check_input(const ButtonCode* user_input, const ButtonCode* sequence, int length);

#endif // GAME_LOGIC_H