#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "Inventory.hpp"
#include "Location.hpp"
#include "WorldMap.hpp"
#include "Item.hpp"
#include "NPC.hpp"
#include "CraftingRecipe.hpp"

class Player {
 private:
    int _health = 100;
    int _hunger = 100;
    Inventory _inventory;
    Location* _currentLocation;
    Weapon* _equippedWeapon;

 public:
    Player(Location* start);
    ~Player();
    int getHealth() const;
    int getHunger() const;
    int inventorySize();

    void moveAction(const std::string& direction, WorldMap* map, bool& valid);
    void takeDamage(int damage);
    void eat(int restore);
    void craft(CraftingRecipe& recipe);
    void buy(Item& item, ShopNPC& shop);
    Inventory& getInventory();
    Item* getItemAt(int ind);
    Location* getCurrent();
   
};

#endif
