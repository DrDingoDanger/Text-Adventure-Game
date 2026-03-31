#include <iostream>
#include "Game.hpp"

Game::Game() : _player(_map.getLocation(0)), _winItem("Emerald") {}

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
    Location* location = _player.getCurrent();
    location->runEncounter(_player);
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
        _display.displayInventory(std::cout, _player.getInventory());
        _display.displayPlayerStats(std::cout, _player);
        std::cout << "Would you like to use an item?\n";
        if (_player.inventorySize() > 0) {
            char ans = _ui.yesOrNo();
            if (ans == 'y') {
                std::cout << "Enter the items associated number.\n";
                int choice = _ui.limitInput(_player.inventorySize());
                Item* temp = _player.getItemAt(choice);
                if (temp->getType() == "material") {
                    std::cout << "This item cannot be used.\n";
                } else if (temp->getType() == "food") {
                    Food* tempF = dynamic_cast<Food*>(temp);
                    int restore = tempF->getHunger();
                    _player.eat(restore);
                    _player.removeItem(tempF);
                } else if (temp->getType() == "weapon") {
                    Weapon* tempW = dynamic_cast<Weapon*>(temp);
                    int power = tempW->getPower();
                    if (power > _player.getAttack()) {
                        _player.setAttack(power);
                        _player.removeItem(tempW);
                    } else {
                        std::cout << "Cannot use item, does not effect attack damage\n";
                    }
                }
            }
        }
    } else if (action == 2) {
        Location* loc = _player.getCurrent();
        _display.drawMap(std::cout, &_map, loc);
    } else if (action == 3) {
        Location* loc = _player.getCurrent();
        _display.displayNPC(std::cout, loc);
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
                Inventory& tempInv = _player.getInventory();
                std::vector<CraftingRecipe*>& tempTrades = tempS->getTrades();
                _display.displayTrades(std::cout, tempTrades, tempInv);
                std::cout << "Would you like to make a trade?\n";
                char ans2 = _ui.yesOrNo();
                if (ans2 == 'y') {
                    std::cout << "Enter the trade's associated number.\n";
                    choice = _ui.limitInput(tempTrades.size());
                    CraftingRecipe* recipe = tempTrades[choice];
                    recipe->craft(tempInv);
                }
            }
        }
    } else if (action == 4) {
        Location* loc = _player.getCurrent();
        Inventory& temp = loc->getInventory();
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
        std::cout << "Invalid input\n";
    }

    if (checkWin() || checkLose()) {
        endGame();
    }

    if (!_isOver) {
        _ui.pressEnter();
    }
}

bool Game::checkWin() {
    return _player.getInventory().hasName(_winItem, 1);
}

bool Game::checkLose() const {
    return _player.getHealth() <= 0 || _player.getHunger() <= 0;
}

void Game::endGame() {
    if (checkWin()) {
        std::cout << "\nYou win! You found the " << _winItem << ".\n";
    } else if (_player.getHealth() <= 0) {
        std::cout << "\nYou lose! Your health reached 0.\n";
    } else if (_player.getHunger() <= 0) {
        std::cout << "\nYou lose! Your hunger reached 0.\n";
    }

    _isOver = true;
}
