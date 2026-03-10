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
    _display.drawMap(std::cout, &_map);
    _display.displayChoices(std::cout);

    int action = _ui.playerAction();

    if (action == 1) {
        std::string direction = _ui.moveDirection();
        _player.move(direction);
    }

    if (checkWin() || checkLose()) {
        endGame();
    }

    _ui.pressEnter();
}

bool Game::checkWin() const {
    //Idk how to create this because the UML shows checkwin as an inventory iteam
    //instead of just a conditoin
    return false;
}

bool Game::checkLose() const {
    return _player.getHealth() <= 0;
}

void Game::endGame() {
    _isOver = true;
}