#include "Mob.hpp"
#include "Player.hpp"

Mob::Mob(std::string name, int health, int attack, Inventory* dropTable)
    : name(name), _health(health), _attack(attack), dropTable(dropTable) {}

Mob::~Mob() {
    delete dropTable;
}

int Mob::getAttack() {
    return _attack;
}

std::string Mob::getName() {
    return name;
}

Inventory* Mob::getInventory() {
    return dropTable;
}

void Mob::takeDamage(int damage) {
    _health -= damage;

    if (_health < 0) {
        _health = 0;
    }
    std::cout << "Current mob health is " << _health << '\n';
}

bool Mob::isDead() {
    return _health == 0;
}
