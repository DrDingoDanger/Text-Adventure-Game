#include "Mob.hpp"

Mob::Mob("Temp", {}, {}, {}) {}

Mob::~Mob() {}

void Mob::attackPlayer(Player _player) {}

void Mob::takeDamage(int damage) {}

bool Mob::isDead() {
    if(health == 0){
        return true;
    }
    return false;
}