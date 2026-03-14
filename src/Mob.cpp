#include "Mob.hpp"
#include "Player.hpp"

Mob::Mob(std::string name, int health, int attack, Inventory dropTable)
    : name(name), health(health), attack(attack), dropTable(dropTable) {}

Mob::~Mob() {}

void Mob::attackPlayer(Player _player) {
    (void)_player;
}

void Mob::takeDamage(int damage) {
    health -= damage;

    if (health < 0) {
        health = 0;
    }
}

bool Mob::isDead() {
    return health == 0;
}
