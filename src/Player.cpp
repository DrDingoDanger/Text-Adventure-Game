#include <iostream>
#include "Player.hpp"

Player::Player(Location* start)
    : _currentLocation(start) {
    _inventory = new Inventory();
    _inventory->add(new Material("Pocket lint"), 2);
    _health = 100;
    _hunger = 100;
    _attack = 1;
    _equippedWeapon = "Fist";
}

Player::~Player() {
    delete _inventory;
}

int Player::getHealth() const {
    return _health;
}

int Player::getHunger() const {
    return _hunger;
}

int Player::getAttack() const {
    return _attack;
}

Inventory* Player::getInventory() {
    return _inventory;
}

std::string Player::getWeapon() const {
    return _equippedWeapon;
}

void Player::setWeapon(Weapon* weapon) {
    _equippedWeapon = weapon->getName();
}

void Player::setAttack(int attack) {
    _attack = attack;
}

bool Player::moveAction(const std::string& direction,
                        WorldMap* map) {
    if (_currentLocation->canExit(direction, map)) {
        _currentLocation = map->updateLocation(direction, _currentLocation);
        return true;
    } else {
        return false;
    }
}

void Player::takeDamage(int damage) {
    _health -= damage;

    if (_health < 0) {
        _health = 0;
    }

    std::cout << "Current player"
              << "\033[0;31m" << " health "
              << "\033[0m" << "is "
              << _health << '\n';
}

void Player::eat(int restore) {
    _hunger += restore;

    if (_hunger > 100) {
        _hunger = 100;
    }

    if (_hunger < 0) {
        _hunger = 0;
    }

    std::cout << "Current player"
              << "\033[0;32m" << " hunger "
              << "\033[0m" << "is "
              << _hunger << '\n';
}

void Player::craft(CraftingRecipe recipe) {
    if (recipe.canCraft(_inventory)) {
        recipe.craft(_inventory);
    }
}

void Player::addItem(Item* item) {
    _inventory->add(item, 1);
}

void Player::removeItem(Item* item) {
    _inventory->remove(item, 1);
}

Item* Player::getItemAt(int ind) {
    return _inventory->get(ind);
}

int Player::inventorySize() {
    return _inventory->size();
}

Location* Player::getCurrent() {
    return _currentLocation;
}
