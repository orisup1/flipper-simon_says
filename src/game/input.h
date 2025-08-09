// input.h
#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

// Logical buttons used by the game
typedef enum ButtonCode {
    ButtonUp = 0,
    ButtonDown = 1,
    ButtonLeft = 2,
    ButtonRight = 3,
    ButtonOk = 4,
    ButtonBack = 5,
} ButtonCode;

// Initialize input/UI (no-op on desktop; required on Flipper)
void input_init(void);
// Deinitialize input/UI (no-op on desktop; required on Flipper)
void input_deinit(void);

// Clear any pending input events
void input_flush_events(void);

// Clear display content
void display_clear(void);

// Wait for OK (center) to start or Back to exit.
// Returns true if OK was pressed, false if Back was pressed.
bool wait_for_ok_or_back(void);

// Read a sequence of directional button presses from the user.
// Only ButtonUp/ButtonDown/ButtonLeft/ButtonRight are captured.
// Returns true if input captured successfully, false if cancelled with Back.
bool get_user_input(ButtonCode* user_input, int length);

// Display visual feedback for a button press
void display_button_press(ButtonCode button);

// Returns a human-readable name for a button
const char* button_name(ButtonCode button);

// Displays a message to the user
void display_message(const char* message);

#endif // INPUT_H