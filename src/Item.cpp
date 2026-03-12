#include "Item.hpp"

Item::Item(std::string name) {
    _name = name;
}

Item::~Item() {}

std::string Item::getName() {
    return _name;
}

Food::Food(std::string name, int value) {
    _name = name;
    _hungerValue = value;
}

Food::~Food() {}

int Food::getHunger() {
    return _hungerValue;
}

void Food::setHunger(int value) {
    _hungerValue = value;
}
