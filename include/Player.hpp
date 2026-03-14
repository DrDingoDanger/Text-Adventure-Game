#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "Inventory.hpp"
#include "Location.hpp"
#include "Item.hpp"
#include "NPC.hpp"
#include "CraftingRecipe.hpp"

class Player {
 private:
    int _health = 100;
    int _hunger = 100;
    Inventory _inventory;
    Location _currentLocation;
    Weapon _equippedWeapon;

 public:
    Player();

    int getHealth() const;
    int getHunger() const;

    void moveAction(const std::string& direction);
    void takeDamage(int damage);
    void eat(Food& food);
    void craft(CraftingRecipe& recipe);
    void buy(Item& item, ShopNPC& shop);
};

#endif
