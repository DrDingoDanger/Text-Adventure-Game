#include "Game.hpp"

#include <iostream>

bool Game::isOver() const {
    return _isOver;
}

void Game::start() {
    _isOver = false;

    while (!_isOver) {
        update();
    }
}

void Game::update() {
    _display.drawMap(std::cout, &_map, nullptr);
    _display.displayAlwaysChoices(std::cout);

    int action = _ui.playerAction();

    if (action == 1) {
        std::string direction = _ui.moveDirection();
        _player.moveAction(direction);
    }

    if (checkWin() || checkLose()) {
        endGame();
    }

    _ui.pressEnter();
}

bool Game::checkWin() const {
    return false;
}

bool Game::checkLose() const {
    return _player.getHealth() <= 0;
}

void Game::endGame() {
    _isOver = true;
}