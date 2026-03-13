#ifndef WORLDMAP_HPP
#define WORLDMAP_HPP

#include <vector>

#include "Location.hpp"

class WorldMap {
    private:
        Location* _current;
        std::vector<Location*> _locations;
//You do not need to make a map in player to manipuulate it
//Give it a parameter that is a map.
    public:
        WorldMap();
        ~WorldMap();
        int getLocationIndex(Location* _current);
};

#endif