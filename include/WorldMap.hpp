#ifndef WORLDMAP_HPP
#define WORLDMAP_HPP

#include <vector>
#include <string>
#include "Location.hpp"

class WorldMap {
 private:
    Location* _current;
    std::vector<Location*> _locations;

 public:
    WorldMap();
    ~WorldMap();
    int getCurrentIndex(Location* current);
    Location* updateLocation(const std::string& _direction, Location* current);
    Location* getLocation(int index);
};

#endif
