#ifndef MOB_HPP
#define MOB_HPP

#include <string>
#include <iostream>
#include "Inventory.hpp"

class Player;

class Mob {
 private:
    std::string name;
    int _health;
    int _attack;
    Inventory* dropTable;

 public:
    Mob(std::string name, int health, int attack, Inventory* dropTable);
    ~Mob();
    int getAttack();
    Inventory* getInventory();
    void takeDamage(int damage);
    std::string getName();
    bool isDead();
};

#endif
