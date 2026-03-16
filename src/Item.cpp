#include "Item.hpp"

Item::Item(std::string name, std::string type) : _name(name), _type(type) {}

Item::~Item() {}

std::string Item::getName() {
    return _name;
}

std::string Item::getType() {
    return _type;
}

Material::Material(std::string name) : Item(name, "material") {}

Material::~Material() {}

Food::Food(std::string name, int value) : Item(name, "food"), _hungerValue(value){}

Food::~Food() {}

int Food::getHunger() {
    return _hungerValue;
}

void Food::setHunger(int value) {
    _hungerValue = value;
}

Weapon::Weapon(std::string name) : Item(name, "weapon") {}

Weapon::~Weapon() {}
