#include "Player.hpp"

Player::Player()
    : _currentLocation("Start", {}, {}, {}), _equippedWeapon() {}

int Player::getHealth() const {
    return _health;
}

int Player::getHunger() const {
    return _hunger;
}

void Player::moveAction(const std::string& direction) {
    (void)direction;
}

void Player::takeDamage(int damage) {
    _health -= damage;

    if (_health < 0) {
        _health = 0;
    }
}

void Player::eat(Food& food) {
    (void)food;
}

void Player::craft(CraftingRecipe& recipe) {
    if (recipe.canCraft(_inventory)) {
        recipe.craft(_inventory);
    }
}

void Player::buy(Item& item, ShopNPC& shop) {
    shop.sellItem(*this, item);
}

