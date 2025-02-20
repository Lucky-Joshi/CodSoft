#include <iostream>
#include <cstdlib>
#include <ctime>

void playGame(); // Function prototype

int main() {
    char playAgain;
    
    std::srand(static_cast<unsigned int>(std::time(0))); // Seed random number generator once

    do {
        playGame();
        std::cout << "Do you want to play again? (Y/N): ";
        std::cin >> playAgain;
    } while (std::toupper(playAgain) == 'Y');

    std::cout << "Thanks for playing! Goodbye.\n";
    return 0;
}

void playGame() {
    int minRange = 1, maxRange = 100, maxAttempts = -1;
    int secretNumber, userGuess, attempts = 0;
    char difficulty;

    std::cout << "\nSelect Difficulty Level:\n";
    std::cout << "E - Easy (1-50, unlimited attempts)\n";
    std::cout << "M - Medium (1-100, max 10 attempts)\n";
    std::cout << "H - Hard (1-200, max 7 attempts)\n";
    std::cout << "Enter your choice (E/M/H): ";
    std::cin >> difficulty;

    switch (std::toupper(difficulty)) {
        case 'E':
            maxRange = 50;
            break;
        case 'M':
            maxRange = 100;
            maxAttempts = 10;
            break;
        case 'H':
            maxRange = 200;
            maxAttempts = 7;
            break;
        default:
            std::cout << "Invalid choice! Defaulting to Medium difficulty.\n";
            maxRange = 100;
            maxAttempts = 10;
    }

    secretNumber = std::rand() % maxRange + minRange; // Generate random number

    std::cout << "Guess the number between " << minRange << " and " << maxRange << ": ";

    do {
        std::cin >> userGuess;
        attempts++;

        int difference = std::abs(secretNumber - userGuess); // Calculate difference

        if (userGuess > secretNumber) {
            std::cout << "Too high! ";
        } else if (userGuess < secretNumber) {
            std::cout << "Too low! ";
        } else {
            std::cout << "🎉 Congratulations! You guessed the number in " << attempts << " attempts.\n";
            break;
        }

        // Hints for guessing
        if (difference <= 5) {
            std::cout << "You're very close! 🔥 Try again: ";
        } else if (difference <= 15) {
            std::cout << "You're getting warm! 😊 Try again: ";
        } else {
            std::cout << "You're far off. ❄️ Try again: ";
        }

        if (maxAttempts != -1 && attempts >= maxAttempts) {
            std::cout << "\nGame Over! You've used all your attempts. The correct number was " << secretNumber << ".\n";
            break;
        }

    } while (true);
}
