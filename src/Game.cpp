#include <iostream>
#include "Game.hpp"
Game::Game() : _player(_map.getLocation(0)) {}

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
        Location* loc = _player.getCurrent();
        _display.drawMap(std::cout, &_map, loc);
        std::string direction = _ui.moveDirection();
        bool valid = true;
        _player.moveAction(direction, &_map, valid);
        while (!valid) {
            std::cout << "You cannot go off the map. Try Again\n";
            direction = _ui.moveDirection();
            _player.moveAction(direction, &_map, valid);
        }
        _player.eat(-5);

    } else if (action == 1) {
        //display inventory
        _display.displayInventory(std::cout, _player.getInventory());
        _display.displayPlayerStats(std::cout, _player);
        //use item
        std::cout << "Would you like to use an item?\n";
        if (_player.inventorySize() > 0) {
            char ans = _ui.yesOrNo();
            if (ans == 'y') {
                std::cout << "Enter the items associated number.\n";
                int choice = _ui.limitInput(_player.inventorySize());
                Item* temp = _player.getItemAt(choice);
                //will need to make this so they cant access non-existing num
                if (temp->getType() == "material" ||
                    temp->getType() == "weapon") {
                    std::cout << "This item cannot be used.";
                } else if (temp->getType() == "food") {
                    Food* tempF = dynamic_cast<Food*>(temp);
                    int restore = tempF->getHunger();
                    _player.eat(restore);
                    _player.removeItem(tempF);
                }
            }
        }
    } else if (action == 2) {
        Location* loc = _player.getCurrent();
        _display.drawMap(std::cout, &_map, loc);
    } else if (action == 3) {
        //display NPCs
        Location* loc = _player.getCurrent();
        _display.displayNPC(std::cout, loc);
        //interact NPC
        std::cout << "Would you like to interact with an NPC?\n";
        char ans = _ui.yesOrNo();
        if (ans == 'y') {
            std::cout << "Enter the NPCs associated number.\n";
            int choice = _ui.limitInput(loc->numOfNPC());
            NPC* temp = loc->getNPC(choice);
            if (temp->getType() == "help") {
                HelpNPC* tempH = dynamic_cast<HelpNPC*>(temp);
                std::cout << '\n' << tempH->giveHint() << '\n';
            } else if (temp->getType() == "shop") {
                ShopNPC* tempS = dynamic_cast<ShopNPC*>(temp);
                _display.displayInventory(std::cout, tempS->getInventory());
                std::cout << "Trading with ShopNPC has not been implemented\n";
            }
        }
    } else if (action == 4) {
        Location* loc = _player.getCurrent();
        Inventory& temp = loc->getInventory();
        //std::cout << "View area resources.\n";
        _display.displayInventory(std::cout, temp);
        std::cout << "Would you like to collect these items?\n";
        char ans = _ui.yesOrNo();
        if (ans == 'y') {
            Inventory& tempP = _player.getInventory();
            while (temp.size() != 0) {
                Item* item = temp.get(0);
                tempP.add(item, 1);
                temp.remove(item, 1);
            }
        }
    } else if (action == 5) {
        _display.gameInstructions(std::cout);
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
