# Flipper Zero Game

## Overview
The Flipper Zero Game is an interactive game designed for the Flipper Zero device. The game challenges users to replicate a series of button presses displayed on the device's direction pad. As users successfully replicate the sequences, the difficulty increases, providing an engaging and fun experience.

## Game Mechanics
- The game starts with a single button press sequence.
- Each time the user successfully replicates the sequence, the length of the sequence increases by one.
- The sequence is generated randomly, ensuring a unique experience with each round.
- Users earn points for each successful replication, with the score displayed on the screen.

## Project Structure
The project is organized into the following directories and files:

- **src/**: Contains the source code for the game.
  - **main.c**: Entry point of the application, initializes the game and manages the game loop.
  - **game/**: Contains game logic and input handling.
    - **game_logic.c**: Implements the core game logic, including sequence generation and score tracking.
    - **game_logic.h**: Header file for game logic functions.
    - **input.c**: Handles user input from the Flipper's direction pad.
    - **input.h**: Header file for input handling functions.
  - **utils/**: Contains utility functions.
    - **random.c**: Implements functions for generating random numbers.
    - **random.h**: Header file for random utility functions.

- **assets/**: Contains documentation related to the assets used in the project.

- **Makefile**: Build instructions for compiling the source files into an executable.

## Building the Game
To build the game, navigate to the project directory and run the following command:

```
make
```

This will compile the source files and create the executable for the Flipper Zero.

## Running the Game
Once built, you can run the game on your Flipper Zero device. Follow the instructions provided in the device's documentation for loading and executing the application.

## Contributing
Contributions to the project are welcome! Please feel free to submit issues or pull requests to enhance the game or fix any bugs.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.