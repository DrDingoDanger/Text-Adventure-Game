#include <iostream>

#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay() {}

ScreenDisplay::~ScreenDisplay() {}

void ScreenDisplay::gameInstructions(std::ostream& out) {
    out << "\n-- Text-Adventure-Game --\n"
    << "Enter the requested information to navigate through the game.\n"
    << "Move: change location by moving left, right, up, or down.\n"
    << "viewInv: Look at the items in your inventory,"
    << "you are given the option to use them.\n"
    << "viewMap: View the world map, your location is in braces.\n"
    << "interactNPC: get a list of NPCs in the"
    << "current location and the ability to interact with them.\n"
    << "areaResources: Look at all available resources in the"
    << "location and the option to collect them.\n"
    << "gameInstructions: View this help message.\n\n";
}

void ScreenDisplay::displayNPC(std::ostream& out, Location*& loc) {
    int num = loc->numOfNPC();
    std::string str;
    out << "NPCs:\n" << "------------------\n";
    //I is tracking current, skipping dups. J numbers each unique.
    for (int i = 0, j = 0; i < num; i++, j++) {
        str += std::to_string(j);
        str += ". ";
        str += loc->getNPC(i)->getName();
        str += "\n";
    }
    out << str << "------------------\n";
}

void ScreenDisplay::drawMap(std::ostream& out,
            WorldMap* map, Location* current) {
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

    for (int i = 0; i < 6; i++) {
        out << i << "- " << base[i] << '\n';
    }
}

void ScreenDisplay::displayPlayerStats(std::ostream& out, Player player) {
    out << "Hunger: " << player.getHunger() << '\n'
        << "Health: " << player.getHealth() << '\n';
}

void ScreenDisplay::displayTrades(std::ostream& out, std::vector<CraftingRecipe*>& trades, Inventory& inv) {
    out << "Trades: \n";
    for (int i = 0; i < trades.size(); i++) {
        CraftingRecipe* trade = trades[i];
        std::vector<std::string> inputNames = trade->getInputs();
        for (int i = 0; i < inputNames.size(); i++) {
            out << inputNames[i];
            if (i < inputNames.size() - 1) {
                out << ", ";
            }
        }
        out << " for ";
        Item* outputItem = trade->getOutput();
        out << outputItem->getName() << " " << std::boolalpha << trade->canCraft(inv);
        out << '\n';
    }
}

void ScreenDisplay::displayInventory(std::ostream& out, Inventory& inv) {
    //Commented stuff is for future implementaion.
    int num = inv.size();
    std::string str;

    out << "Inventory:\n" << "------------------\n";

    //I is tracking current, skipping dups. J numbers each unique.
    for (int i = 0, j = 0; i < num; i++, j++) {
       // int mult = 1;
        str += std::to_string(j);
        str += ". ";
        str += inv.get(i)->getName();
        /*
        while (i + 1 < num && inv.get(i) == inv.get(i + 1)) {
            mult++;
            i++;
        }
        
        if (mult > 1) {
            str += ' ';
            str += std::to_string(mult);
            str += 'x';       
        }
*/
        str += "\n";
    }

    out << str << "------------------\n";
}
