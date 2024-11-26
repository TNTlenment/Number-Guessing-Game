#ifndef GUESSNUMBERGAME_H
#define GUESSNUMBERGAME_H

#include <vector>
#include <optional>
#include <memory>

class GuessNumberGame {
private:
    std::unique_ptr<int> numberToGuess;  // Random number to guess
    std::unique_ptr<int> attemptsLeft;   // Remaining attempts
    std::unique_ptr<int> attemptsUsed;   // Attempts used
    std::vector<int> guesses;            // User guesses

    [[nodiscard]] int generateRandomNumber() const; // Generate a random number
    void printRules() const;                        // Display game rules
    [[nodiscard]] int selectDifficulty() const;     // Select difficulty level
    void playRound();                               // Main game logic
    [[nodiscard]] std::optional<int> getUserGuess() const; // Get user input
    [[nodiscard]] bool processGuess(int guess) const;      // Process user guess
    void printGuesses() const;                             // Display all guesses

public:
    GuessNumberGame();  // Constructor
    ~GuessNumberGame(); // Destructor
    void start();       // Start the game
};

#endif // GUESSNUMBERGAME_H
