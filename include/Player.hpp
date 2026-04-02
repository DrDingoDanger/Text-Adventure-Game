#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "Inventory.hpp"
#include "Location.hpp"
#include "WorldMap.hpp"
#include "Item.hpp"
#include "NPC.hpp"
#include "CraftingRecipe.hpp"
class WorldMap;
class Player {
 private:
    int _health;
    int _hunger;
    int _attack;
    Inventory* _inventory;
    Location* _currentLocation;
    Weapon* _equippedWeapon;

 public:
    Player(Location* start);
    ~Player();
    int getHealth() const;
    int getHunger() const;
    int getAttack() const;
    int inventorySize();

    bool moveAction(const std::string& direction, WorldMap* map);
    void takeDamage(int damage);
    void eat(int restore);
    void setAttack(int attack);
    void craft(CraftingRecipe recipe);
    void buy(const Item& item, const ShopNPC& shop);
    void addItem(Item* item);
    void removeItem(Item* item);
    Inventory* getInventory();
    Item* getItemAt(int ind);
    Location* getCurrent();
};
#endif
