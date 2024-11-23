# Tic Tac Toe with Timer

This project is a simple implementation of the Tic Tac Toe game in C++ with the following features:
- **5-Second Timer**: Players must input their move within 5 seconds, or they lose their turn.
- **Dynamic Turn Switching**: Automatically switches turns on timeout or invalid input.
- **Win Checking**: Detects win conditions for rows, columns, and diagonals.
- **Interactive Gameplay**: Players can choose their marker ('X' or 'O').

## Features
1. **Board Display**: Dynamic board rendering after each turn.
2. **Player Turn Management**: Players alternate turns, with a strict timer enforced.
3. **Win Condition Validation**: The game ends if a player achieves three markers in a row.
4. **Draw Condition**: The game ends in a tie if all slots are filled without a winner.

## How to Run
1. Compile the code:
   ```bash
   g++ -o tictactoe tictactoe.cpp
