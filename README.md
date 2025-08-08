# Flipper Zero Simon Says electronic game
## V1.0
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

## Current Version Overview

- **Features**
  - **Start menu**: waits for OK (center) to start; Back exits the app.
  - **Simon Says gameplay**: sequence grows by one step each round.
  - **Reliable input**: uses Flipper GUI InputEvent queue; ignores long presses.
  - **Back behavior**: ignored during input entry (prevents accidental exit); honored in the menu.
  - **Screen handling**: sequence is shown step-by-step and cleared before your turn.
  - **Desktop simulator**: same logic runs in terminal for quick testing.

- **Controls (on Flipper)**
  - **D-Pad**: Enter the sequence during your turn (Up/Down/Left/Right).
  - **OK**: Start game at the menu; ignored during input.
  - **Back**: Exit from the menu; ignored during input.

## Build & Run

- **Desktop (Simulator)**
  - Build: 
    ```bash
    make
    ```
  - Run: 
    ```bash
    ./flipper_zero_game
    ```

- **Flipper Zero (FAP)**
  - Install uFBT (once):
    ```bash
    python3 -m pip install --upgrade ufbt
    ```
  - Initialize SDK in this repo (once):
    ```bash
    ufbt init
    ```
  - Build the FAP:
    ```bash
    make fap
    # or
    ufbt build
    ```
  - Install & launch on device:
    ```bash
    ufbt launch
    ```
    The built file is also available at `~/.ufbt/build/simonsays.fap`.

## Project Structure Notes
- **Flipper app manifest**: `flipper-zero-game/application.fam` defines metadata and entrypoint `simonsays_main`.
- **Conditional compilation**: Desktop path uses the `DESKTOP` macro; Flipper path is default under uFBT.
- **Input/Display**: Implemented in `src/game/input.c` with separate device/desktop code paths.