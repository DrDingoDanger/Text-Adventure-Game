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
        // Actual location switching is not in the UML.
        // For now, this confirms movement is allowed.
    }
}

void Player::takeDamage(int damage) {
    _health -= damage;

    if (_health < 0) {
        _health = 0;
    }
}

//No public way to get food so this is the minimal way i had to do it
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