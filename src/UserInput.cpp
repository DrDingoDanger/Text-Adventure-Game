#include "UserInput.hpp"

#include <iostream>
#include <limits>
#include <string>

std::string UserInput::moveDirection() {
    std::string direction;
    std::cout << "Enter direction (left, right, up, down): ";
    std::cin >> direction;
    return direction;
}
//GET NUM 0<=X<MAX
int UserInput::limitInput(int max) {
    int choice;
    bool goodInput = false;
    std::cout << "Enter choice: ";
    while (goodInput == false) {
        std::cin >> choice;
        if (choice < max && choice >= 0) {
            goodInput = true;
        } else {
            std::cout << "Input is not a valid item";
        }
    }
    return choice;
}
//GET ACTION NUMBER
int UserInput::playerAction() {
    int action;
    std::cout << "Enter action number: ";
    std::cin >> action;
    return action;
}

char UserInput::yesOrNo() {
    char ans;
    std::cout << "Enter y/n: ";
    std::cin >> ans;
    return ans;
}

void UserInput::pressEnter() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
