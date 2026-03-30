#include "Player.hpp"

Player::Player(Location* start)
    : _currentLocation(start), _equippedWeapon(nullptr) {
        _inventory.add(new Material("Thing"), 1);
        _health = 100;
        _hunger = 100;
        _attack = 1;
    }

Player::~Player() {}

int Player::getHealth() const {
    return _health;
}

int Player::getHunger() const {
    return _hunger;
}

int Player::getAttack() const {
    return _attack;
}

Inventory& Player::getInventory() {
    return _inventory;
}
//CHANGES PLAYERS CURRENT LOCATION
void Player::moveAction(const std::string& direction,
                        WorldMap* map, bool& valid) {
    if (_currentLocation->canExit(direction, map)) {
        _currentLocation = map->updateLocation(direction, _currentLocation);
        valid = true;
    } else {
        valid = false;
    }
}
//MODIFIES PLAYER HEALTH
void Player::takeDamage(int damage) {
    _health -= damage;

    if (_health < 0) {
        _health = 0;
    }
    std::cout << "Current player health is " << _health << '\n';
}
//MODIFIES PLAYER HUNGER
void Player::eat(int restore) {
    _hunger += restore;
    if (_hunger > 100) {
        _hunger = 100;
    }
}

void Player::craft(CraftingRecipe& recipe) {
    if (recipe.canCraft(_inventory)) {
        recipe.craft(_inventory);
    }
}

void Player::buy(Item& item, ShopNPC& shop) {
    //shop.sellItem(*this, item);
}

void Player::addItem(Item* item) {
    _inventory.add(item, 1);
}

void Player::removeItem(Item* item) {
    _inventory.remove(item, 1);
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
