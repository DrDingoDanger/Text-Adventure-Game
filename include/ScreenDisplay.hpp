#ifndef SCREENDISPLAY_HPP
#define SCREENDISPLAY_HPP

#include <iostream>

#include "WorldMap.hpp"
#include "Location.hpp"

class ScreenDisplay {
 private:
    std::string base[4] = {"move", "viewInv", "viewMap", "interactNPC"};

 public:
    ScreenDisplay();
    ~ScreenDisplay();
    void drawMap(std::ostream& out, WorldMap* map, Location* current);
    void displayAlwaysChoices(std::ostream& out);
};

#endif
