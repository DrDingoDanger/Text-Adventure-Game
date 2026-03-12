#include "UserInput.hpp"

#include <iostream>
#include <limits>
#include <string>

std::string UserInput::moveDirection() {
    std::string direction;
    std::cout << "Enter direction: ";
    std::cin >> direction;
    return direction;
}

int UserInput::playerAction() {
    int action;
    std::cout << "Enter action: ";
    std::cin >> action;
    return action;
}

void UserInput::pressEnter() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
