#include <iostream>

#include "ScreenDisplay.hpp"

ScreenDisplay::ScreenDisplay() {}

ScreenDisplay::~ScreenDisplay() {}

void ScreenDisplay::showTitleScreen(std::ostream& out) {
    out << "\033[H\033[2J";
    out << "==========================================================\n";
    out << "                    TEXT ADVENTURE\n";
    out << "==========================================================\n\n";
    out << "              /\\                     /\\\n";
    out << "             /  \\       /\\          /  \\\n";
    out << "            /    \\     /  \\        /    \\\n";
    out << "           /      \\   /    \\      /      \\\n";
    out << "          /________\\ /______\\    /________\\\n\n";
    out << "          ~ ~ ~  QUEST FOR THE \033[32mEMERALD\033[0m  ~ ~ ~\n\n";
    out << "           Explore. Collect. Trade. Survive.\n\n";
    out << "==========================================================\n";
}

void ScreenDisplay::gameInstructions(std::ostream& out) {
    out << "\033[H\033[2J"
    << "\n               -- \033[0;36mText-Adventure-Game\033[0m --\n\n"
    << "Enter the requested information to navigate through the game.\n\n"
    << " -\033[0;32mMove\033[0m"
    << ": \033[4;36mChange location\033[0m by moving left, right, up, or down.\n"
    << " -\033[0;32mView Inventory\033[0m"
    << ": Look at the \033[4;36mitems in your inventory\033[0m,"
    << " you are given the option to use them.\n"
    << " -\033[0;32mView Map\033[0m"
    << ": View the world map, your \033[4;36mlocation is in brackets\033[0m.\n"
    << " -\033[0;32mFind NPC's\033[0m"
    << ": Check the area for any \033[4;36mshop or dialog NPC's\033[0m."
    << " NPC's have \033[4;36mmutiple dialog options\033[0m and"
    << " can give \033[4;36mhints\033[0m.\n"
    << " -\033[0;32mCheck Area\033[0m"
    << ": \033[4;36mCollect resources\033[0m from the area and"
    << " \033[4;36mfight mobs for their drops\033[0m.\n"
    << " -\033[0;32mGame Instructions\033[0m"
    << ": View this help message.\n"
    << " -\033[0;32mQuit\033[0m"
    << ": End the game.\n\n";
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
        out << "  ";

        for (int j = 0; j < 3; j++) {
            int index = j + (i * 3);
            Location* location = map->getLocation(index);

            if (index == cIndex) {
                out << "[\033[0;36m"
                    << location->getName()
                    << "\033[0m]  ";
            } else {
                out << " "
                    << location->getName();
                if (j != 2) {
                    out << "   ";
                }
            }
        }

        out << '\n';
    }
    out << "Current area: "
        << map->getLocation(cIndex)->getName()
        << "\n\n";
}

void ScreenDisplay::displayAlwaysChoices(std::ostream& out) {
    out << "What do you want to do?\n";

    for (int i = 0; i < 7; i++) {
        out << (i + 1) << "- " << base[i] << '\n';
    }
}

void ScreenDisplay::displayPlayerStats(std::ostream& out,
            const Player& player) {
    out << "\033[0;31m" << "Health: "
        << std::to_string(player.getHealth()) << '\n'
        << "\033[0;32m" << "Hunger: "
        << std::to_string(player.getHunger()) << '\n'
        << "\033[0m" << player.getWeapon() << " : "
        << std::to_string(player.getAttack()) << " dmg\n";
}

void ScreenDisplay::displayTrades(std::ostream& out,
    const std::vector<CraftingRecipe*>& trades, Inventory* inv) {
    int numT = trades.size();

    out << "\033[H\033[2J\033[0;34m" << "Trades: \n"
        << "\033[0m" << "------------------\n";

    for (int i = 0; i < numT; i++) {
        out << (i + 1) << ". ";
        std::vector<std::string> inputNames = trades[i]->getInputs();
        int numI = inputNames.size();

        for (int j = 0; j < numI; j++){
            int mult = 1;
            out << inputNames[j];

            while (j + 1 < numI && inputNames[j] == inputNames[j + 1]) {
                mult++;
                j++;
            }

            if (mult > 1) {
                    out << ' ' << std::to_string(mult) << 'x';
            }

            if (j < numI - 1){
                    out << " & ";
            }
        }

        out << " for "
            << trades[i]->getOutput()->getName()
            << '\n';
    }

    out << "------------------\n\n";
    this->displayInventory(out, inv);
}

void ScreenDisplay::displayInventory(std::ostream& out, Inventory* inv) {
    int num = inv->size();
    std::string str;

    out << "\033[0;34m" << "Inventory:\n"
        << "\033[0m" << "------------------\n";

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
