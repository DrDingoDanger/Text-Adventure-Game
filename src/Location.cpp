#include <iostream>

#include "Location.hpp"
#include "WorldMap.hpp"

Location::Location() {}

Location::~Location() {}

void Location::enter(Player* _player) {}

void Location::runEncounter(Player* _player, Mob* _mob) {}

bool Location::canExit(const std::string& _direction, WorldMap* map) {
    int index = map->getLocationIndex(this);

    if (_direction == "up" && index < 3 ||
        _direction == "down" && index > 5) {
        return false;

    } else if ( _direction == "left" && index % 3 == 0 ||
        _direction == "right" && index % 3 == 2) {
        return false;
    }

    return true;
}

std::string Location::getName() {
    return name;
}

NPC* Location::getNPC(int index) {
    return _npcCollection[index];
}

CraftingRecipe* Location::getRecipe(int index) {
    return _recipes[index];
}

Mob* Location::getMob(int index) {
    return _mobs[index];
}
