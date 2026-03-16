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

    _display.displayAlwaysChoices(std::cout);

    int action = _ui.playerAction();

    if (action == 0) {
        std::string direction = _ui.moveDirection();
        _player.moveAction(direction);

    } else if (action == 1) {
        //display inventory
        std::cout << "\nThis will be Inventory\n";
        //use item
        std::cout << "Would you like to use an item?\n";
        char ans = _ui.yesOrNo();
        if(ans == 'y') {
            std::cout << "Enter the items associated number.\n";
            int choice = _ui.playerAction();
            Item* temp = _player.getItemAt(choice);
            //will need to make this so they cant access non-existing num
            if (temp->getType() == "material" || temp->getType() == "weapon") {
                std::cout << "This item cannot be used.";
            } else if (temp->getType() == "food") {
                Food* tempF = dynamic_cast<Food*>(temp);
                int restore = tempF->getHunger();
                _player.eat(restore);
            }
        }
    } else if (action == 2) {
        _display.drawMap(std::cout, &_map, nullptr);
    } else if (action == 3) {
        std::cout << "\nThis will give list of NPCs to interact with.\n";
    } else {
        std::cout << "Invalid input";
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