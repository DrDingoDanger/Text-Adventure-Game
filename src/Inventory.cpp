#include "Inventory.hpp"

Inventory::Inventory() {}

Inventory::~Inventory() {}

void Inventory::add(Item* _item, int count) {
    for (int i = 0; i < count; i++) {
        _items.push_back(_item);
    }
}

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

int Inventory::has(Item* _item, int count) {
    (void)count;

    int found = 0;
    for (Item* i : _items) {
        if (i->getName() == _item->getName()) {
            found++;
        }
    }
    return found;
}

int Inventory::size() {
    return _items.size();
}

Item* Inventory::get(int index) {
    return _items[index];
}
