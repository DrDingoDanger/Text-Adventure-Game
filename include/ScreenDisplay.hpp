#ifndef SCREENDISPLAY_HPP
#define SCREENDISPLAY_HPP

#include <iostream>

#include "WorldMap.hpp"
#include "Location.hpp"

class ScreenDisplay {
 private:
    std::string base[6] = {"move", "viewInv", "viewMap", "interactNPC", "areaResources", "gameInstructions"};

 public:
    ScreenDisplay();
    ~ScreenDisplay();
    void gameInstructions(std::ostream& out);
    void drawMap(std::ostream& out, WorldMap* map, Location* current);
    void displayAlwaysChoices(std::ostream& out);
};

#endif
