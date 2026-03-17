#include <iostream>

#include "Location.hpp"
#include "WorldMap.hpp"

Location::Location(std::string name, std::vector<NPC*> npcCollection,
    std::vector<CraftingRecipe*> recipes, std::vector<Mob*> mobs, Inventory areaResources, float encounterRate)
    : name(name), _npcCollection(npcCollection), _recipes(recipes), _mobs(mobs), _areaResources(areaResources), encounterRate(encounterRate) {}

Location::~Location() {}

void Location::enter(Player* _player) {}

void Location::runEncounter(Player* _player, Mob* _mob) {}

bool Location::canExit(const std::string& _direction, WorldMap* map) {
    int index = map->getCurrentIndex(this);

    if ((_direction == "up" && index < 3) ||
        (_direction == "down" && index > 5)) {
        return false;
    } else if ((_direction == "left" && index % 3 == 0) ||
               (_direction == "right" && index % 3 == 2)) {
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

Inventory& Location::getInventory() {
    return _areaResources;
}

int Location::numOfNPC() {
    return _npcCollection.size();
}

Mountain::Mountain(std::string name, std::vector<NPC*> _npcCollection,
         std::vector<CraftingRecipe*> _recipes, std::vector<Mob*> _mobs, Inventory inv) :
         Location(name, _npcCollection, _recipes, _mobs, inv, 0.6){
}

Mountain::~Mountain() {}

Field::Field(std::string name, std::vector<NPC*> _npcCollection,
         std::vector<CraftingRecipe*> _recipes, std::vector<Mob*> _mobs, Inventory inv) :
         Location(name, _npcCollection, _recipes, _mobs, inv, 0.3){
}

Field::~Field() {}