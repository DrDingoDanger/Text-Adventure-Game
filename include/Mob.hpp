#ifndef MOB_HPP
#define MOB_HPP

#include "Inventory.hpp"

class Mob {
    private:
        std::string name;
        int health;
        int attack;
        Inventory dropTable;

    public:
        Mob(std::string name, int health, int attack, Inventory dropTable);
        ~Mob();
        void attackPlayer(Player _player);
        void takeDamage(int damage);
        bool isDead();
};