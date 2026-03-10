#include "Player.hpp"

#include "Food.hpp"
#include "CraftingRecipe.hpp"
#include "Item.hpp"
#include "ShopNPC.hpp"

int Player::getHealth() const {
    return _health;
}

int Player::getHunger() const {
    return _hunger;
}

void Player::move(const std::string& direction) {
    if (_currentLocation.canExit(direction)) {
        // Actual location switching/entering should be handled
        // wherever the map navigation logic is implemented.
    }
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
