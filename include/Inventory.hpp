#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <algorithm>
#include <string>
#include "Item.hpp"

class Inventory {
 private:
    std::vector<Item*> _items;

 public:
    Inventory();
    ~Inventory();
    void add(Item* _item, int _count);
    void remove(Item* _item, int count);
    void removeByName(std::string name, int count);
    bool has(Item* _item, int count);
    bool hasName(std::string name, int count);
    int size();
    Item* get(int index);
};

#endif
