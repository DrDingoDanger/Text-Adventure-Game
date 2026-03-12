#ifndef USERINPUT_HPP
#define USERINPUT_HPP

#include <string>

class UserInput {
 public:
    std::string moveDirection();
    int playerAction();
    void pressEnter();
};
#endif
