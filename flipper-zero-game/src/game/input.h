// input.h
#ifndef INPUT_H
#define INPUT_H

// Initialize input/UI (no-op on desktop; required on Flipper)
void input_init(void);
// Deinitialize input/UI (no-op on desktop; required on Flipper)
void input_deinit(void);

// Reads a sequence of button presses from the user (0=UP, 1=DOWN, 2=LEFT, 3=RIGHT)
void get_user_input(int* user_input, int length);

// Function to display the button press feedback
void display_button_press(int button);

// Returns a human-readable name for a button index
const char* button_name(int button);

// Displays a message to the user
void display_message(const char* message);

#endif // INPUT_H