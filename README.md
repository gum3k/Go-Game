# Go-Game

**Go-Game** is a simple C++ implementation of the traditional board game Go. This program provides a text-based interface to play Go on a grid, where players alternate placing black and white stones on the board. The game includes basic mechanics such as capturing stones and handling the "ko" rule.

## Features
- Play Go on a customizable board size (9x9, 13x13, 19x19, or a custom size).
- Alternate between two players (black and white) placing stones.
- Capture stones by surrounding them.
- Handle the "ko" rule to prevent endless loops.
- Save and load game states to/from files.
- Display the board visually in the terminal.

## Files Overview

- **main.cpp**: The main file containing the game logic, board initialization, stone placement, scoring, and game flow.
- **conio2.h**: Provides console input/output utilities, such as moving the cursor and changing text color.
- **conio2.cpp**: Implementation of the console utilities defined in `conio2.h`.

## Requirements
- A C++ compiler (supports C++11 or later).
- `conio2.h` library (used for handling console input/output).

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/gum3k/Go-Game.git
   ```

2. Compile the program:
   ```bash
   g++ -o go-game main.cpp conio2.cpp
   ```

3. Run the game:
   ```bash
   ./go-game
   ```

## Usage

Once the game starts, you can play by placing black and white stones on the Go board. The game alternates between two players. You can use the following controls:

- `i` - Place a stone on the board.
- `s` - Save the current game state to a file.
- `l` - Load a saved game state from a file.
- `h` - Start the game with a handicap (press `esc` to end handicap mode).
- `q` - Quit the game.
- `n` - Start a new game.

### Example:
1. Select the board size (9x9, 13x13, or 19x19) by pressing the corresponding number key.
2. Use the arrow keys to move the cursor and place stones with the `i` key.
3. Press `enter` to confirm the placement of a stone.
4. Use `s` to save the game or `l` to load a previously saved game.

## Game Mechanics
- Players alternate placing stones on the board.
- Stones are "captured" when they are surrounded on all four sides by the opponent’s stones.
- The "ko" rule is implemented to prevent a player from making a move that would recreate the board position that just existed, which could result in an infinite loop.
