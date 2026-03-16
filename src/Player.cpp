#include "Player.hpp"

Player::Player(Location* start)
    : _currentLocation(start), _equippedWeapon(nullptr){}

int Player::getHealth() const {
    return _health;
}

int Player::getHunger() const {
    return _hunger;
}

Inventory& Player::getInventory() {
    return _inventory;
}
void Player::moveAction(const std::string& direction, WorldMap* map, bool& valid) {
    //(void)direction;
    if(_currentLocation->canExit(direction, map)) {
        _currentLocation->updateLocation(direction, _currentLocation);
        valid = true;
    } else {
        valid = false;
    }
}

void Player::takeDamage(int damage) {
    _health -= damage;

    if (_health < 0) {
        _health = 0;
    }
}

void Player::eat(int restore) {
    _hunger += restore;
    if(_hunger > 100) {
        _hunger = 100;
    }
}

void Player::craft(CraftingRecipe& recipe) {
    if (recipe.canCraft(_inventory)) {
        recipe.craft(_inventory);
    }
}

void Player::buy(Item& item, ShopNPC& shop) {
    shop.sellItem(*this, item);
}

Item* Player::getItemAt(int ind) {
    return _inventory.get(ind);
}

int Player::inventorySize() {
    return _inventory.size();
}

Location* Player::getCurrent() {
    return _currentLocation;
}

Inventory* Player::getInventory() {
    return _inventory;
}