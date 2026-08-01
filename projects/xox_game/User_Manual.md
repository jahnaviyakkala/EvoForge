# XOX Game User Manual

## Introduction

This manual provides step-by-step instructions on how to use the XOX game. The game can be run in either single-player mode against an AI or multiplayer mode for two players.

## CLI Usage

1. **Start the Game:**
   - Open your terminal.
   - Navigate to the project directory:
     ```bash
     cd /home/pss/project/projects/xox_game
     ```
   - Run the game using Python:
     ```bash
     python main.py
     ```

2. **Select Mode:**
   - Upon starting, you will be prompted to select a mode:
     ```
     Select mode:
     1. Single-player (AI)
     2. Multiplayer
     Enter your choice (1/2):
     ```
   - Choose `1` for single-player or `2` for multiplayer.

3. **Gameplay:**
   - The game board will be displayed in the terminal.
   - Players take turns entering their move by specifying the row and column numbers.
   - Example input:
     ```
     Enter your move (row col): 1 2
     ```

4. **Winning or Losing:**
   - The game will announce the winner when a player gets three of their marks in a row, column, or diagonal.
   - If all spaces are filled without a winner, the game is a draw.

5. **Exit Procedures:**
   - To exit the game, you can type `exit` at any prompt:
     ```
     Enter your move (row col): exit
     ```

## Available Menu Options

- **Single-player Mode:** Play against an AI.
- **Multiplayer Mode:** Play with another player.

## Example Inputs and Expected Outputs

**Example Input:**
