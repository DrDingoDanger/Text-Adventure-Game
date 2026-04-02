#include <iostream>
#include "Game.hpp"

Game::Game() : _player(_map.getLocation(0)) {}

Game::~Game() {}

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
    int action = _ui.playerAction();

// MOVE
    if (action == 1) {
        Location* loc = _player.getCurrent();
        _display.drawMap(std::cout, &_map, loc);
        std::string direction = _ui.moveDirection();
        bool valid = _player.moveAction(direction, &_map);
        //Check if valid direction
        while (!valid) {
            std::cout << "You cannot go off the map. Try Again\n";
            direction = _ui.moveDirection();
            valid = _player.moveAction(direction, &_map);
        }
        location = _player.getCurrent();
        location->runEncounter(&_player);
        _player.eat(-10);
        std::cout << '\n';
// CHECK STATS/INVENTORY
    } else if (action == 2) {
        //Display stats & inventory
        std::cout << "\033[H\033[2J";
        _display.displayInventory(std::cout, _player.getInventory());
        _display.displayPlayerStats(std::cout, _player);
        //Check if inventory is empty
        if (_player.inventorySize() > 0) {
            std::cout << "\nWould you like to use an item?\n";
            char ans = _ui.yesOrNo();
            if (ans == 'y') {
                //User chooses item from inventory
                std::cout << "Enter the items associated number.\n";
                int choice = _ui.limitInput(_player.inventorySize() + 1);
                Inventory* invT = _player.getInventory();
                Item* temp = invT->get(0);
                //Display input -> item location converter
                std::string prev = "";
                for (int index = 0, numSet = 0;
                        index < _player.inventorySize(); index++) {
                    Item* current = invT->get(index);
                    if (current->getName() != prev) {
                        numSet++;
                        prev = current->getName();
                    }
                    if (numSet == choice) {
                        temp = current;
                        break;
                    }
                }
                //Check item type
                if (temp->getType() == "material") {
                    std::cout << temp->getName()
                              << " material cannot be used.\n\n";
                } else if (temp->getType() == "food") {
                    //Increases player hunger
                    Food* tempF = dynamic_cast<Food*>(temp);
                    int restore = tempF->getHunger();
                    _player.takeDamage(-(restore / 2));
                    _player.eat(restore);
                    _player.removeItem(tempF);
                } else if (temp->getType() == "weapon") {
                    Weapon* tempW = dynamic_cast<Weapon*>(temp);
                    int power = tempW->getPower();
                    //Raises dps if item is higher then current
                    if (power > _player.getAttack()) {
                        std::cout << temp->getName() << " equipped!\n";
                        _player.setAttack(power);
                        _player.setWeapon(tempW);
                        _player.removeItem(tempW);
                    } else {
                        std::cout << temp->getName()
                                  << " is already equipped\n";
                    }
                }
            }
        }
        std::cout << '\n';
// CHECK MAP
    } else if (action == 3) {
        //Display map
        Location* loc = _player.getCurrent();
        _display.drawMap(std::cout, &_map, loc);
// NPC/TRADING
    } else if (action == 4) {
        Location* loc = _player.getCurrent();
        _display.displayNPC(std::cout, loc);
        std::cout << "Would you like to interact with an NPC?\n";
        char ans = _ui.yesOrNo();
        if (ans == 'y') {
            //User chooses NPC from location
            std::cout << "Enter the NPCs associated number.\n";
            int choice = _ui.limitInput(loc->numOfNPC() + 1);
            NPC* temp = loc->getNPC(choice - 1);
            //Check NPC type
            if (temp->getType() == "help") {
                HelpNPC* tempH = dynamic_cast<HelpNPC*>(temp);
                std::cout << tempH->giveHint() << "\n";
            } else if (temp->getType() == "shop") {
                //Sets up trades and displays player & NPC inventory
                ShopNPC* tempS = dynamic_cast<ShopNPC*>(temp);
                Inventory* invT = _player.getInventory();
                std::vector<CraftingRecipe*>& tempTrades = tempS->getTrades();
                _display.displayTrades(std::cout, tempTrades, invT);
                std::cout << "Would you like to make a trade?\n";
                char ansr = _ui.yesOrNo();
                if (ansr == 'y') {
                    //User choose trade from NPC inventory
                    std::cout << "Enter the trade's associated number.\n";
                    choice = _ui.limitInput(tempTrades.size() + 1);
                    CraftingRecipe* recipe = tempTrades[choice - 1];
                    recipe->craft(invT);
                }
            }
        }
        std::cout << '\n';
// CHECK LOCATION
    } else if (action == 5) {
        std::cout << "\033[H\033[2J";
        Location* loc = _player.getCurrent();
        Inventory* temp = loc->getInventory();
        //Displays location inventory
        if (temp->size() != 0) {
            _display.displayInventory(std::cout, temp);
            std::cout << "Would you like to collect these items?\n";
            char ans = _ui.yesOrNo();
            if (ans == 'y') {
                //Transfer items to player inventory
                Inventory* tempP = _player.getInventory();
                while (temp->size() != 0) {
                    Item* item = temp->get(0);
                    tempP->add(item, 1);
                    temp->remove(item, 1);
                }
            }
        } else {
            std::cout << "\nThere are no more resources in the area\n\n";
        }
        std::cout << '\n';
        _ui.pressEnter();
        //Runs possible encounter for area
        location->runEncounter(&_player);
// INSTRUCTIONS
    } else if (action == 6) {
        _display.gameInstructions(std::cout);
    } else {
// DEFAULT
        std::cout << "Invalid input";
    }
    //Checks game condition
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
