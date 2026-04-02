#include <iostream>

#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay() {}

ScreenDisplay::~ScreenDisplay() {}

void ScreenDisplay::gameInstructions(std::ostream& out) {
    out << "\033[H\033[2J"
    << "\n               -- \033[0;36mText-Adventure-Game\033[0m --\n\n"
    << "Enter the requested information to navigate through the game.\n\n"
    << " -\033[0;32mMove\033[0m"
    << ":change location by moving left, right, up, or down.\n"
    << " -\033[0;32mviewInv\033[0m"
    << ": Look at the items in your inventory,"
    << "you are given the option to use them.\n"
    << " -\033[0;32mviewMap\033[0m"
    << ": View the world map, your location is in braces.\n"
    << " -\033[0;32minteractNPC\033[0m"
    << ": get a list of NPCs in the"
    << "current location and the ability to interact with them.\n"
    << " -\033[0;32mareaResources\033[0m"
    << ": Look at all available resources in the"
    << "location and the option to collect them.\n"
    << " -\033[0;32mgameInstructions\033[0m"
    << ": View this help message.\n\n";
}

void ScreenDisplay::displayNPC(std::ostream& out, Location* loc) {
    int num = loc->numOfNPC();
    std::string str;
    out << "\033[H\033[2J\033[0;34m" << "NPCs:\n"
        << "\033[0m" << "------------------\n";
    for (int i = 0; i < num; i++) {
        str += std::to_string(i + 1);
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
    out << "\033[H\033[2J\033[2;1H";
    for (int i = 0; i < 3; i++) {
        std::string str = "  ";

        for (int j = 0; j < 3; j++) {
            int index = j + (i * 3);
            Location* location = map->getLocation(index);

            if (index == cIndex) {
                str += "[\033[0;36m";
                str += location->getName();
                str += "\033[0m]  ";
            } else {
                str += " ";
                str += location->getName();
                if (j != 2) {
                    str += "   ";
                }
            }
        }

        out << str << '\n';
    }
}

void ScreenDisplay::displayAlwaysChoices(std::ostream& out) {
    out << "What do you want to do?\n";

    for (int i = 0; i < 6; i++) {
        out << (i + 1) << "- " << base[i] << '\n';
    }
}

void ScreenDisplay::displayPlayerStats(std::ostream& out,
            const Player& player) {
    out << "\033[0;31m" << "Health: "
        << std::to_string(player.getHealth()) << '\n'
        << "\033[0;32m" << "Hunger: "
        << std::to_string(player.getHunger()) << '\n'
        << "\033[0m" << "Attack: "
        << std::to_string(player.getAttack()) << '\n';
}

void ScreenDisplay::displayTrades(std::ostream& out,
    const std::vector<CraftingRecipe*>& trades, Inventory* inv) {
    out << "\033[H\033[2J\033[0;34m" << "Trades: \n"
        << "\033[0m" << "------------------\n";
    for (int i = 0; i < trades.size(); i++) {
        out << (i + 1) << ". ";
        CraftingRecipe* trade = trades[i];
        std::vector<std::string> inputNames = trade->getInputs();
        for (int j = 0; j < inputNames.size(); j++) {
            out << inputNames[j];
            if (j < inputNames.size() - 1) {
                out << " & ";
            }
        }
        out << " for ";
        Item* outputItem = trade->getOutput();
        out << outputItem->getName();
        out << " (" << std::boolalpha << trade->canCraft(inv) << ") ";
        out << '\n';
    }

    out << "------------------\n\n";
    this->displayInventory(out, inv);
}

void ScreenDisplay::displayInventory(std::ostream& out, Inventory* inv) {
    int num = inv->size();
    std::string str;

    out << "\033[0;34m" << "Inventory:\n"
        << "\033[0m" << "------------------\n";

    //I is tracking current, skipping dups. J numbers each unique.
    for (int i = 0, j = 1; i < num; i++, j++) {
        int mult = 1;
        str += std::to_string(j);
        str += ". ";
        str += inv->get(i)->getName();

        while (i + 1 < num && inv->get(i)->getName()
                    == inv->get(i + 1)->getName()) {
            mult++;
            i++;
        }

        if (mult > 1) {
            str += ' ';
            str += std::to_string(mult);
            str += 'x';
        }

        str += "\n";
    }

    out << str << "------------------\n";
}

