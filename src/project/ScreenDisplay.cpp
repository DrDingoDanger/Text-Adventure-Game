#include <fstream>
#include <iomanip>
#include <iostream>

#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay() {}

ScreenDisplay::~ScreenDisplay() {}

void ScreenDisplay::drawMap(ostream out, WorldMap* map) {
    //int index = map->getLocationIndex()
    //add a 'isCurrent' function.
    for(auto i = 0; i < 3; i++) {
        std::string str;
        for(auto j = 0; j < 3; j++) {
            str += map[j + (i * 3)];
            if(j != 2) str += "  ";
        }
        out << str + '\n';
    }
}

void ScreenDisplay::displayChoices(ostream out) {}