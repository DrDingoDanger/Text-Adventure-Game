#include "UserInput.hpp"

#include <iostream>
#include <limits>
#include <string>

std::string UserInput::moveDirection() {
    std::string direction;
    std::cout << "Enter direction (left, right, up, down): ";
    while (std::cin >> direction &&
          (direction != "left" && direction != "right" &&
           direction != "up"   && direction != "down")) {
        std::cout << "Invalid input. Directions only!\n"
                  << "Try again: ";
    }
    return direction;
}
//GET NUM 0<X<MAX
int UserInput::limitInput(int max) {
    int choice;
    bool goodInput = false;
    std::cout << "Enter choice: ";
    while (goodInput == false) {
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Numbers only!\n"
                      << "Try again: ";
        }
        if (choice < max && choice > 0) {
                goodInput = true;
            } else {
                std::cout << "Input is not a valid item\n"
                      << "Try again: ";
            }
    }
    return choice;
}
//GET ACTION NUMBER
int UserInput::playerAction() {
    int action;
    std::cout << "Enter action number: ";
    while (!(std::cin >> action)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Numbers only!\n"
                  << "Try again: ";
    }
    return action;
}

char UserInput::yesOrNo() {
    char ans;
    std::cout << "Enter y/n: ";
    while (std::cin >> ans &&
          ((ans != 'y' && ans != 'Y') &&
           (ans != 'n' && ans != 'N'))) {
        std::cout << "Invalid input. Characters only!\n"
                  << "Try again: ";
    }
    return ans;
}

void UserInput::pressEnter() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::cout << "\n-------------------------"
              << "---------------------------";
    std::cout << "\033[H\033[2J\n";
}
