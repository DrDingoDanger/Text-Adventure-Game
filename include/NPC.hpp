#ifndef NPC_HPP
#define NPC_HPP

#include <vector>
#include <string>
#include <random>
#include "Inventory.hpp"
#include "Item.hpp"
#include "CraftingRecipe.hpp"

class Location;
class Player;

class NPC {
 private:
    std::string _name;
    std::string _type;
 public:
    NPC(std::string name, std::string type);
    virtual ~NPC();
    std::string getName();
    std::string getType();
};

class HelpNPC : public NPC {
 private:
    std::vector<std::string> diaOptions;
    int loseGame;
 public:
    HelpNPC(std::string name, std::vector<std::string> dia);
    ~HelpNPC();
    std::string giveHint();
    void reduceCount();
    int getCount();
};

class ShopNPC : public NPC {
 private:
    std::vector<CraftingRecipe*> _trades;

 public:
    ShopNPC(std::string name, std::vector<CraftingRecipe*> trades);
    ~ShopNPC();
    //void sellItem(Player& player, Item& item);

    std::vector<CraftingRecipe*>& getTrades();
};

#endif
