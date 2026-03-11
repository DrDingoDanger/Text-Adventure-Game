#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <algorithm>
#include "Item.hpp"

class Inventory {
 private:
    std::vector<Item*> _items;
 public:
    Inventory();
    ~Inventory();
    void add(Item* _item, int _count);
    void remove(Item* _item, int count);
    int has(Item* _item, int count);
};
#endif
