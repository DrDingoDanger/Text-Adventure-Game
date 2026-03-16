#include <iostream>

#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay() {}

ScreenDisplay::~ScreenDisplay() {}

void ScreenDisplay::drawMap(std::ostream& out, WorldMap* map, Location* current) {
    int cIndex = 0;

    if (current != nullptr) {
        cIndex = map->getCurrentIndex(current);
    }

    for (int i = 0; i < 3; i++) {
        std::string str;

        for (int j = 0; j < 3; j++) {
            int index = j + (i * 3);
            Location* location = map->getLocation(index);

            if (index == cIndex) {
                str += '[';
                str += location->getName();
                str += ']';
            } else {
                str += location->getName();
            }

            if (j != 2) {
                str += "  ";
            }
        }

        out << str << '\n';
    }

    //out << map->getLocation(cIndex)->getName() << '\n';
}

void ScreenDisplay::displayAlwaysChoices(std::ostream& out) {
    out << "What do you want to do?\n";

    for (int i = 0; i < 5; i++) {
        out << i << "- " << base[i] << '\n';
    }
}

void ScreenDisplay::displayInventory(std::ostream& out, Inventory* inventory){
    //Commented stuff is for future implementaion.
    int temp = inventory->size();
    std::string str;

    out << "Inventory:\n" << "------------------\n";

    //I is tracking current, skipping dups. J numbers each unique.
    for (int i = 0, j = 1; i < temp; i++, j++) {
        //int mult = 1;
        str += std::to_string(j);
        str += ". ";
        str += inventory->get(i);

        /*while (i + 1 < temp && inventory->get(i) == inventory->get(i + 1)) {
            mult++;
            i++;
        }
        
        if (mult > 1) {
            str += ' ';
            str += std::to_string(mult);
            str += 'x';       
        }*/

        str += "\n";
    }

    out << str << "------------------\n";
}