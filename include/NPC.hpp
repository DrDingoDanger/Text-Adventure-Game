#ifndef NPC_HPP
#define NPC_HPP

#include <vector>
#include <string>
#include "Inventory.hpp"
#include "Item.hpp"

class Location;
class Player;

class NPC {
 private:
    std::string _name;
    Location* _location;

 public:
    NPC(std::string name, Location* location);
    virtual ~NPC();
};

class HelpNPC : public NPC {
 private:
    std::vector<std::string> diaOptions;

 public:
    HelpNPC(std::string name, Location* location, std::vector<std::string> dia);
    ~HelpNPC();
    std::string giveHint();
};

class ShopNPC : public NPC {
 private:
    Inventory stock;

 public:
    ShopNPC(std::string name, Location* location, std::vector<Item*> items);
    ~ShopNPC();
    void sellItem(Player& player, Item& item);
};

#endif
