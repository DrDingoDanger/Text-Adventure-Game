#include <iostream>

#include "Location.hpp"
#include "WorldMap.hpp"

Location::Location(std::string name, std::vector<NPC*> npcCollection,
    std::vector<CraftingRecipe*> recipes, std::vector<Mob*> mobs,
    Inventory areaResources, float encounterRate)
    : name(name), _npcCollection(npcCollection), _recipes(recipes),
     _mobs(mobs), _areaResources(areaResources), encounterRate(encounterRate) {}

Location::~Location() {}

void Location::runEncounter(Player* player) {
    for (int i = 0; i < _mobs.size(); i++) {
        Mob* mob = _mobs[i];
        std::cout << "Encounter #" << i+1 << ": ";
        std::cout << mob->getName() << '\n';
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        float encounter = dis(gen);
        std::cout << encounter << std::endl;
        if (encounter < encounterRate) {
            player->takeDamage(mob->getAttack());
            mob->takeDamage(player->getAttack());
        } else {
            std::cout << "You did not encounter this mob\n";
        }
    }
    auto it = _mobs.begin();
    while (it != _mobs.end()) {
        Mob* mob = *it;
        if (mob && mob->isDead()) {
            Inventory& mobInv = mob->getInventory();
            while (mobInv.size() > 0) {
                Item* item = mobInv.get(0);
                player->getInventory()->add(item, 1);
                mobInv.remove(item, 1);
            }
            delete mob;
            it = _mobs.erase(it);
        } else {
            ++it;
        }
    }
    _mobs.erase(std::remove_if(_mobs.begin(), _mobs.end(),
    [](Mob* mob) {
        return mob->isDead();
    }), _mobs.end());
}

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

Inventory* Location::getInventory() {
    return &_areaResources;
}

int Location::numOfNPC() {
    return _npcCollection.size();
}

Mountain::Mountain(std::string name, std::vector<NPC*> _npcCollection,
         std::vector<CraftingRecipe*> _recipes,
         std::vector<Mob*> _mobs, Inventory inv) :
         Location(name, _npcCollection, _recipes, _mobs, inv, 0.6) {
}

Mountain::~Mountain() {}

Field::Field(std::string name, std::vector<NPC*> _npcCollection,
         std::vector<CraftingRecipe*> _recipes,
         std::vector<Mob*> _mobs, Inventory inv) :
         Location(name, _npcCollection, _recipes, _mobs, inv, 0.3) {
}

Field::~Field() {}
