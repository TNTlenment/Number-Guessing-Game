#include "GuessNumberGame.h"
#include <iostream>
#include <random>
#include <ranges>

// Constructor: Initialize members
GuessNumberGame::GuessNumberGame() 
    : numberToGuess(std::make_unique<int>(0)),
      attemptsLeft(std::make_unique<int>(0)),
      attemptsUsed(std::make_unique<int>(0)) {
    std::cout << "Welcome to the Guess the Number Game! Object created.\n";
}

// Destructor: Log object destruction
GuessNumberGame::~GuessNumberGame() {
    std::cout << "Thank you for playing Guess the Number Game! Object destroyed.\n";
}

// Generate a random number
int GuessNumberGame::generateRandomNumber() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 100);
    return dis(gen);
}

// Display game rules
void GuessNumberGame::printRules() const {
    std::cout << R"(
Welcome to the Guess the Number Game!

Rules:
1. The computer randomly selects a number between 1 and 100.
2. You must guess the number within a limited number of attempts.
3. After each guess, you will be told whether your guess is too high or too low.
4. The game ends if you guess correctly or run out of attempts.

Good luck!
)" << std::endl;
}

// Select difficulty level
int GuessNumberGame::selectDifficulty() const {
    std::string choice;
    std::cout << "Select difficulty level:\n";
    std::cout << "1. Easy (10 attempts)\n";
    std::cout << "2. Medium (7 attempts)\n";
    std::cout << "3. Hard (5 attempts)\n";
    std::cout << "Enter your choice (1, 2, or 3): ";
    std::cin >> choice;

    if (choice == "1") return 10;
    if (choice == "2") return 7;
    if (choice == "3") return 5;

    std::cout << "Invalid choice, defaulting to Easy.\n";
    return 10;
}



// Get user input
std::optional<int> GuessNumberGame::getUserGuess() const {
    int guess = 0;
    std::cout << "You have " << *attemptsLeft << " attempts remaining.\n";
    std::cout << "Enter your guess (1 to 100): ";

    if (!(std::cin >> guess)) {
        std::cin.clear(); // 清除错误状态
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 丢弃无效输入
        std::cout << "Invalid input, please enter an integer.\n";
        return std::nullopt;
    }

    if (guess >= 1 && guess <= 100) {
        return guess;
    } else {
        std::cout << "Invalid input, please enter a number between 1 and 100.\n";
        return std::nullopt;
    }
}

// Process user guess
bool GuessNumberGame::processGuess(int guess) const {
    if (guess == *numberToGuess) {
        return true;
    } else if (guess < *numberToGuess )[[likely]] {
        std::cout << "Too low!\n";
    } else {
        std::cout << "Too high!\n";
    }
    return false;
}

// Display all user guesses
void GuessNumberGame::printGuesses() const {
    std::cout << "Your guesses: ";
    for (const int g : guesses) {
        std::cout << g << " ";
    }
    std::cout << "\n";
}

// Main game logic
void GuessNumberGame::playRound() {
    *attemptsUsed = 0;
    guesses.clear();
    *numberToGuess = generateRandomNumber();
    *attemptsLeft = selectDifficulty();

    std::cout << "\nGame starts!\n";

    while (*attemptsLeft > 0) {
        auto userGuess = getUserGuess();
        if (!userGuess) continue; // Skip if invalid input

        guesses.push_back(*userGuess); // Record the guess
        (*attemptsUsed)++;
        (*attemptsLeft)--;

        if (processGuess(*userGuess)) {
            std::cout << "Congratulations! You guessed correctly in " << *attemptsUsed << " attempts!\n";
            printGuesses();
            return;
        }
    }

    std::cout << "\nSorry, you ran out of attempts. The correct number was " << *numberToGuess << ".\n";
    printGuesses();
}

// Start the game
void GuessNumberGame::start() {
    printRules();
    char playAgain;

    do {
        playRound();
        std::cout << "Would you like to play again? (y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    std::cout << "Thanks for playing! Goodbye!\n";
}
