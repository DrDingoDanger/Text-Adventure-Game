#include <fstream>
#include <iomanip>
#include <iostream>

#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay() {}

ScreenDisplay::~ScreenDisplay() {}

void ScreenDisplay::drawMap(std::ostream& out, WorldMap* map, Location* current) {
    int cIndex  = map->getCurrentIndex(current);

    //Make 3 rows
    for (auto i = 0; i < 3; i++) {
        std::string str;
        //Make individual row
        for (auto j = 0; j < 3; j++) {
            //check if current location
            if (j + (i * 3) == cIndex) {
                str += '[';
                str += map[j + (i * 3)]->getName();
                str += ']';
            } else {
                str += map[j + (i * 3)]->getName();
            }
            //chech if end of row
            if (j != 2) str += "  ";
        }
        //Print row
        out << str + '\n';
    }
    out << map[cIndex]->getName() + '\n';
}

void ScreenDisplay::displayAlwaysChoices(std::ostream& out) {
    out << "What do you want to do?" + '\n';
    //display options (defined in private)
    for (auto i = 0; i < 4; i++) {
        out << std::to_string(i) + '- ' + base[i] + '\n';
    }
}