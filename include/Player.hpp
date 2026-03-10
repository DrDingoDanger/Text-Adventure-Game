#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "Inventory.hpp"
#include "Location.hpp"
#include "Weapon.hpp"

class Food;
class CraftingRecipe;
class Item;
class ShopNPC;

class Player {
private:
    int _health = 100;
    int _hunger = 100;
    Inventory _inventory;
    Location _currentLocation;
    Weapon _equippedWeapon;

public:
    Player() = default;

    int getHealth() const;
    int getHunger() const;

    void move(const std::string& direction);
    void takeDamage(int damage);
    void eat(Food& food);
    void craft(CraftingRecipe& recipe);
    void buy(Item& item, ShopNPC& shop);
};

#endif