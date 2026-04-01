#include <algorithm>
#include <exception>

#include "WorldMap.hpp"
//MAKE THE MAP
WorldMap::WorldMap() : _current(nullptr) {
    std::vector<std::string> dia;
    dia.push_back("Trade items with NPC to gain new items.");
    dia.push_back("Moving between locations costs"
                  "hunger, eating restores hunger.");
    dia.push_back("Enjoy this game or else you. are. cursed.");
    dia.push_back("I love this gamehousen.");
    dia.push_back("Another random dialogue option");
    std::vector<std::string> emeraldCost;
    emeraldCost.push_back("Apple");
    emeraldCost.push_back("Coal");
    std::vector<std::string> chickenCost;
    chickenCost.push_back("Banana");
    chickenCost.push_back("Banana");

    for (int i = 0; i < 3; i++) {
        std::vector<NPC*> npcs;
        std::vector<CraftingRecipe*> trades;
        std::vector<Mob*> mobs;
        Inventory* inv = new Inventory();
        Inventory* invZ = new Inventory();
        Inventory* invS = new Inventory();

        trades.push_back(new CraftingRecipe(emeraldCost,
            new Material("Emerald")));
        trades.push_back(new CraftingRecipe(chickenCost,
            new Food("Chicken", 2)));
        mobs.push_back(new Mob("Zombie", 5, 5, invZ));
        mobs.push_back(new Mob("Skelly", 3, 8, invS));
        npcs.push_back(new HelpNPC("Danhousen", dia));
        npcs.push_back(new ShopNPC("Hangman", trades));
        inv->add(new Food("Apple", 3), 1);
        inv->add(new Material("Coal"), 4);
        inv->add(new Weapon("woodSword", 3), 1);
        invZ->add(new Material("Flesh"), 1);
        invS->add(new Material("Bone"), 1);

        _locations.push_back(new Mountain("M"+std::to_string(i),
                             npcs, {}, mobs, inv));
    }

    for (int i = 3; i < 6; i++) {
        std::vector<NPC*> npcs;
        std::vector<CraftingRecipe*> trades;
        std::vector<Mob*> mobs;
        Inventory* inv = new Inventory();
        Inventory* invZ = new Inventory();
        Inventory* invS = new Inventory();


        trades.push_back(new CraftingRecipe(emeraldCost,
            new Material("Emerald")));
        trades.push_back(new CraftingRecipe(chickenCost,
            new Food("Chicken", 2)));
        mobs.push_back(new Mob("Zombie", 5, 5, invZ));
        mobs.push_back(new Mob("Skelly", 3, 8, invS));
        npcs.push_back(new HelpNPC("Danhousen", dia));
        npcs.push_back(new ShopNPC("Hangman", trades));
        inv->add(new Food("Banana", 4), 6);
        inv->add(new Material("Grass"), 1);
        invZ->add(new Material("Flesh"), 1);
        invS->add(new Material("Bone"), 1);


        _locations.push_back(new Field("F"+std::to_string(i),
                             npcs, {}, mobs, inv));
    }

    for (int i = 6; i < 9; i++) {
        std::vector<NPC*> npcs;
        std::vector<CraftingRecipe*> trades;
        std::vector<Mob*> mobs;
        Inventory* inv = new Inventory();
        Inventory* invZ = new Inventory();
        Inventory* invS = new Inventory();

        trades.push_back(new CraftingRecipe(emeraldCost,
            new Material("Emerald")));
        trades.push_back(new CraftingRecipe(chickenCost,
            new Food("Chicken", 2)));
        mobs.push_back(new Mob("Zombie", 5, 5, invZ));
        mobs.push_back(new Mob("Skelly", 3, 8, invS));
        npcs.push_back(new HelpNPC("Danhousen", dia));
        npcs.push_back(new ShopNPC("Hangman", trades));
        inv->add(new Food("Banana", 4), 6);
        inv->add(new Material("Grass"), 1);
        invZ->add(new Material("Flesh"), 1);
        invS->add(new Material("Bone"), 1);

        _locations.push_back(new Mountain("M"+std::to_string(i),
                             npcs, {}, mobs, inv));
    }

    if (!_locations.empty()) {
        _current = _locations[0];
    }
}

WorldMap::~WorldMap() {
    for (Location* location : _locations) delete location;
    _locations.clear();
}

Location* WorldMap::updateLocation(const std::string& _direction,
                                   Location* current) {
    int index = getCurrentIndex(current);

    if (_direction == "up") {
        if (index - 3 >= 0) return _locations[index - 3];
    } else if (_direction == "down") {
        if (index + 3 <= 8) return _locations[index + 3];
    } else if (_direction == "left") {
        if (index - 1 >= 0) return _locations[index - 1];
    } else if (_direction == "right") {
        if (index + 1 <= 8) return _locations[index + 1];
    }

    return current;
}

int WorldMap::getCurrentIndex(Location* current) {
    auto it = std::find(_locations.begin(), _locations.end(), current);

    if (it == _locations.end()) {
        return 0;
    }

    return it - _locations.begin();
}

Location* WorldMap::getLocation(int index) {
    return _locations[index];
}
