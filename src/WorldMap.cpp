#include <iostream>
#include <algorithm>
#include <iterator>

#include "WorldMap.hpp"
#include "Location.hpp"
#include "NPC.hpp"
#include "Mob.hpp"
#include "CraftingRecipe.hpp"

WorldMap::WorldMap() {
    for (auto i = 0; i < 8; i++) {
            _locations.push_back(new Location("Temp", {}, {}, {}));
    }
}

WorldMap::~WorldMap() {
    while (!_locations.empty()) {
        delete _locations.back();
        _locations.pop_back();
    }
}

int WorldMap::getCurrentIndex(Location* _current) {
    return auto it = std::find(_locations.begin(), _locations.end(), _current) - _locations.begin();
}
