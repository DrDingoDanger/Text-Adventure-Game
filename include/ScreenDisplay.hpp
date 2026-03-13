#ifndef SCREENDISPLAY_HPP
#define SCREENDISPLAY_HPP

#include <iostream>

#include "WorldMap.hpp"


class ScreenDisplay {
    public:
        ScreenDisplay();
        ~ScreenDisplay();
        void drawMap(ostream out, WorldMap* map);
        void displayChoices(ostream out); 
};

#endif