#ifndef WORLDMAP_HPP
#define WORLDMAP_HPP

#include <vector>

#include "Location.hpp"

class WorldMap {
    private:
        Location* _current;
        std::vector<Location*> _locations;

    public:
        WorldMap();
        ~WorldMap();
        int getLocationIndex(Location* _current);
};

#endif