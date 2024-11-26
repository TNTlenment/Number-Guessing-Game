#include "GuessNumberGame.h"
#include <limits>
#include <iostream>
#include <memory>

int main() {
    // Use a smart pointer to manage the GuessNumberGame object
    auto game = std::make_unique<GuessNumberGame>();
    game->start();
    std::cout << "Press Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 使用 std::numeric_limits 清空缓冲区
    std::cin.get();
    return 0;
}


