#include "Game.hpp"

#include <iostream>

Game::Game() : _player(_map.getLocation(0)){
}

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
        if(_player.inventorySize() > 0) {
            char ans = _ui.yesOrNo();
            if(ans == 'y') {
                std::cout << "Enter the items associated number.\n";
                int choice = _ui.limitInput(_player.inventorySize());
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
        }
    } else if (action == 2) {
        _display.drawMap(std::cout, &_map, _player.getCurrent());
    } else if (action == 3) {
        //display NPCs
        std::cout << "\nThis will be NPC list\n";
        //interact NPC
        std::cout << "Would you like to interact with an NPC?\n";
        char ans = _ui.yesOrNo();
        if(ans == 'y') {
            std::cout << "Enter the NPCs associated number.\n";
            Location* loc = _player.getCurrent();
            int choice = _ui.limitInput(loc->numOfNPC());
            NPC* temp = loc->getNPC(choice);
            if (temp->getType() == "help") {
                HelpNPC* tempH = dynamic_cast<HelpNPC*>(temp);
                tempH->giveHint();
            } else if (temp->getType() == "shop") {

            }
        }
    } else if (action == 4) {
        std::cout << "View area resources.\n";
        std::cout << "Would you like to collect these items?\n";
        char ans = _ui.yesOrNo();
        if(ans == 'y') {
            Location* loc = _player.getCurrent();
            Inventory temp = loc->getInventory();
            Inventory tempP = _player.getInventory();
            while(temp.size() != 0) {
                Item* item = temp.get(0);
                tempP.add(item, 1);
                temp.remove(item, 1);
            }
        }
    } else if (action == 5) {
        //_display.displayGameInstructions();
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