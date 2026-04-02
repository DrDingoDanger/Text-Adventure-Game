#include "Game.hpp"

int main() {
    std::cout << "\n-------------------------"
              << "---------------------------"
              << "\033[H\033[2J";
    Game game;
    game.start();
    return 0;
}
