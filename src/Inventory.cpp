#include "Inventory.hpp"

Inventory::Inventory() {}

Inventory::~Inventory() {}
//ADD ITEM TO INVENTORY
void Inventory::add(Item* _item, int count) {
    for (int i = 0; i < count; i++) {
        _items.push_back(_item);
    }
}
//REMOVE ITEM FROM INVENTORY
void Inventory::remove(Item* _item, int count) {
    int removed = 0;
    auto it = _items.begin();

    while (it != _items.end() && removed < count) {
        if ((*it)->getName() == _item->getName()) {
            it = _items.erase(it);
            removed++;
        } else {
            ++it;
        }
    }
}

void Inventory::removeByName(std::string name, int count) {
    int removed = 0;
    auto it = _items.begin();
    while (it != _items.end() && removed < count) {
        if ((*it)->getName() == name) { //
            it = _items.erase(it);
            removed++;
        } else {
            ++it;
        }
    }
}

//CHECK IF INVENTORY HAS NUMBER OF ITEM
bool Inventory::has(Item* _item, int count) {
    int found = 0;
    for (Item* i : _items) {
        if (i->getName() == _item->getName()) {
            found++;
        }
    }
    return found >= count;
}

bool Inventory::hasName(std::string name, int count) {
    int found = 0;
    for (Item* i : _items) {
        if (i->getName() == name) { //
            found++;
        }
    }
    return found >= count;
}

//RETURN CURRENT INVENTORY SIZE
int Inventory::size() {
    return _items.size();
}
//GET ITEM AT INDEX
Item* Inventory::get(int index) {
    return _items[index];
}
