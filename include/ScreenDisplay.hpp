#ifndef SCREENDISPLAY_HPP
#define SCREENDISPLAY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "WorldMap.hpp"
#include "Location.hpp"
#include "Player.hpp"
#include "Mob.hpp"

class ScreenDisplay {
 private:
    std::string base[7] = {"Move", "View Inventory", "View Map", "Find NPC's",
      "Check Area", "Game Instructions", "Quit"};

 public:
    ScreenDisplay();
    ~ScreenDisplay();
    void showTitleScreen(std::ostream& out);
    void gameInstructions(std::ostream& out);
    void displayNPC(std::ostream& out, Location* loc);
    void drawMap(std::ostream& out, WorldMap* map, Location* current);
    void displayAlwaysChoices(std::ostream& out);
    void displayPlayerStats(std::ostream& out, const Player& player);
    void displayTrades(std::ostream& out,
      const std::vector<CraftingRecipe*>& trades, Inventory* inv);
    void displayInventory(std::ostream& out, Inventory* inv);
};

#endif
