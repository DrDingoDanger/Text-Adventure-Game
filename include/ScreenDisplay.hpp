#ifndef SCREENDISPLAY_HPP
#define SCREENDISPLAY_HPP

#include <iostream>
#include <string>

#include "WorldMap.hpp"
#include "Location.hpp"
#include "Player.hpp"

class ScreenDisplay {
 private:
    std::string base[6] = {"move", "viewStats", "viewMap", "interactNPC",
      "areaResources", "gameInstructions"};

 public:
    ScreenDisplay();
    ~ScreenDisplay();
    void gameInstructions(std::ostream& out);
    void displayNPC(std::ostream& out, Location*& loc);
    void drawMap(std::ostream& out, WorldMap* map, Location* current);
    void displayAlwaysChoices(std::ostream& out);
    void displayPlayerStats(std::ostream& out, Player player);
    void displayTrades(std::ostream& out, std::vector<CraftingRecipe*>& trades);
    void displayInventory(std::ostream& out, Inventory& inv);
};

#endif
