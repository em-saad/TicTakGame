#include <iostream>
#include <thread>  // For std::this_thread::sleep_for and std::thread
#include <chrono>  // For std::chrono::seconds
#include <cstdlib> // For system("CLS")
#include <atomic>  // For atomic flags
using namespace std;

char board[3][3] = { {'1', '2', '3'},
                     {'4', '5', '6'},
                     {'7', '8', '9'} };
char player1Marker, player2Marker, currentMarker;
int currentPlayer;

// Function to display the board
void displayBoard() {
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

// Function to place a marker
bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentMarker;
        return true;
    } else {
        return false;
    }
}

// Function to check for a win
bool checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) || 
            (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || 
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return true;
    }
    return false;
}

// Function to switch player
void switchPlayer() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
    currentMarker = (currentPlayer == 1) ? player1Marker : player2Marker;
}

// Function to handle a player's turn with a timer
bool playerTurn() {
    atomic<bool> inputReceived(false);
    int slot;

    cout << "Player " << currentPlayer << "'s turn. You have 5 seconds to enter a slot: ";

    thread inputThread([&]() {
        cin >> slot;
        inputReceived = true;
    });

    // Wait for input or timeout
    for (int i = 0; i < 50; i++) {
        this_thread::sleep_for(chrono::milliseconds(100));
        if (inputReceived) break;
    }

    if (inputThread.joinable()) {
        inputThread.detach();
    }

    if (!inputReceived) {
        cout << "\nTime's up! Player " << currentPlayer << " missed their turn.\n";
        return false; // Player missed their turn
    }

    if (slot < 1 || slot > 9 || !placeMarker(slot)) {
        cout << "Invalid input or slot already taken! Skipping turn.\n";
        return false;
    }
    return true;
}

// Main game function
void playGame() {
    cout << "Player 1, choose your marker (X or O): ";
    cin >> player1Marker;

    if (player1Marker == 'X' || player1Marker == 'x') {
        player1Marker = 'X';
        player2Marker = 'O';
    } else if (player1Marker == 'O' || player1Marker == 'o') {
        player1Marker = 'O';
        player2Marker = 'X';
    } else {
        cout << "Invalid marker! Defaulting Player 1 to 'X' and Player 2 to 'O'.\n";
        player1Marker = 'X';
        player2Marker = 'O';
    }

    cout << "Player 1: " << player1Marker << "\n";
    cout << "Player 2: " << player2Marker << "\n";

    currentPlayer = 1;
    currentMarker = player1Marker;

    for (int i = 0; i < 9; i++) {
        displayBoard();
        if (!playerTurn() || checkWin()) {
            if (checkWin()) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!\n";
                return;
            }
        }
        switchPlayer();
    }
    displayBoard();
    cout << "It's a tie!\n";
}

// Main function
int main() {
    cout << "Welcome to Tic Tac Toe with a 5-second timer per turn!\n";
    playGame();
    return 0;
}
