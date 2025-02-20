#include <iostream>

const int SIZE = 3;
char board[SIZE][SIZE];
char currentPlayer;

void initializeBoard();
void displayBoard();
bool makeMove(int row, int col);
bool checkWin();
bool checkDraw();
void switchPlayer();

int main() {
    char playAgain;
    do {
        initializeBoard();
        currentPlayer = 'X';
        bool gameWon = false;
        bool gameDraw = false;

        while (!gameWon && !gameDraw) {
            displayBoard();
            int row, col;
            std::cout << "Player " << currentPlayer << ", enter your move (row and column): ";
            std::cin >> row >> col;

            if (makeMove(row - 1, col - 1)) {
                gameWon = checkWin();
                if (!gameWon) {
                    gameDraw = checkDraw();
                    switchPlayer();
                }
            } else {
                std::cout << "Invalid move. Try again.\n";
            }
        }

        displayBoard();
        if (gameWon) {
            std::cout << "Player " << currentPlayer << " wins!\n";
        } else {
            std::cout << "The game is a draw!\n";
        }

        std::cout << "Do you want to play again? (Y/N): ";
        std::cin >> playAgain;
    } while (std::toupper(playAgain) == 'Y');

    std::cout << "Thanks for playing! Goodbye.\n";
    return 0;
}

void initializeBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    std::cout << "\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << board[i][j];
            if (j < SIZE - 1) std::cout << " | ";
        }
        std::cout << "\n";
        if (i < SIZE - 1) std::cout << "--|---|--\n";
    }
    std::cout << "\n";
}

bool makeMove(int row, int col) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        return true;
    }
    return false;
}

bool checkWin() {
    // Check rows and columns
    for (int i = 0; i < SIZE; ++i) {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
        return true;
    }
    return false;
}

bool checkDraw() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}
