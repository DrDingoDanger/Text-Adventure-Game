#ifndef USERINPUT_HPP
#define USERINPUT_HPP

#include <string>

class UserInput {
 public:
    std::string moveDirection();
    int playerAction();
    int limitInput(int max);
    char yesOrNo();
    void pressEnter();
};
#endif
