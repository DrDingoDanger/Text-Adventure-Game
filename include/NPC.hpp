#ifndef ITEM_HPP
#define ITEM_HPP

#include <vector>
#include <string>
#include <iostream>
#include <random>
#include "Location.hpp"
#include "Inventory.hpp"

class NPC {
    private:
        std::string _name;
        Location _location;
    public:
        NPC(std::string name, Location location);
        ~NPC();
};

class HelpNPC : public NPC {
    private:
        vector<string> diaOptions;
    public:
        HelpNPC(vector<std::string> dia);
        ~HelpNPC();
        std::string giveHint();
};

class ShopNPC : public NPC {
    private:
        Inventory stock;
    public:
        ShopNPC(vector<Item*> items);
        ~ShopNPC();
        buyItem(Item* _item);
        sellItem(Item* _item);
};
#endif
