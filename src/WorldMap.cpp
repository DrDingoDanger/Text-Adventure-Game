#include <algorithm>

#include "WorldMap.hpp"

WorldMap::WorldMap() : _current(nullptr) {
    Inventory inv;
    inv.add(new Food("Apple", 3), 1);
    inv.add(new Material("Diamond"), 2);
    std::vector<std::string> dia;
    dia.push_back("Trade items with NPC to gain new items.");
    dia.push_back("Moving between locations costs"
                  "hunger, eating restores hunger.");
    dia.push_back("Enjoy this game or else you. are. cursed.");
    dia.push_back("I love this gamehousen.");
    dia.push_back("Another random dialogue option");
    std::vector<NPC*> npcs;
    npcs.push_back(new HelpNPC("Danhousen", dia));
    npcs.push_back(new ShopNPC("Hangman", inv));
    Inventory inv1;
    inv1.add(new Food("Apple", 3), 1);
    inv1.add(new Material("Coal"), 4);
    for (int i = 0; i < 3; i++) {
        _locations.push_back(new Mountain("M"+std::to_string(i),
                             npcs, {}, {}, inv1));
    }
    Inventory inv2;
    inv2.add(new Food("Banana", 4), 6);
    inv2.add(new Material("Grass"), 1);
    for (int i = 3; i < 6; i++) {
        _locations.push_back(new Field("F"+std::to_string(i),
                             npcs, {}, {}, inv2));
    }
    for (int i = 6; i < 9; i++) {
        _locations.push_back(new Mountain("M"+std::to_string(i),
                             npcs, {}, {}, inv1));
    }
    if (!_locations.empty()) {
        _current = _locations[0];
    }
}

WorldMap::~WorldMap() {
    while (!_locations.empty()) {
        delete _locations.back();
        _locations.pop_back();
    }
}

Location* WorldMap::updateLocation(const std::string& _direction,
                                   Location* current) {
    int index = getCurrentIndex(current);

    if (_direction == "up") {
        return _locations[index - 3];
    } else if (_direction == "down") {
        return _locations[index + 3];
    } else if (_direction == "left") {
        return _locations[index - 1];
    } else if (_direction == "right") {
        return _locations[index + 1];
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
