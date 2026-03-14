#include <algorithm>

#include "WorldMap.hpp"

WorldMap::WorldMap() : _current(nullptr) {
    for (int i = 0; i < 9; i++) {
        _locations.push_back(new Location("Temp", {}, {}, {}));
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
