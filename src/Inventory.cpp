#include "Inventory.cpp"

Inventory::Inventory() {}

Inventory::~Inventory() {}

Inventory::add(Item* _item, int count) {
    for(int i = 0; i < count; i++) {
        _items.push_back(_item);
    }
}

Inventory::remove(Item* _item, int count) {
    int removed = 0;
    auto it = _items.begin();
    int found = std::count_if(_items.begin(), _items.end(), [&](Item* i));
    if(found < count) {
        ScreenDisplay screen;
        screen.display(std::cout, "Not enough items in this inventory for this action.");
        return;
    }
    while (it != _items.end() && removed < count) {
        if ((*it)->getName() == item->getName()) {
            delete *it;
            it = _items.erase(it);
            removed++;
        } else {
            ++it;
        }
    }
}

int Inventory::has(Item* _item, int count) {
    int found = std::count_if(_items.begin(), _items.end(), [&](Item* i));
    return found;
}