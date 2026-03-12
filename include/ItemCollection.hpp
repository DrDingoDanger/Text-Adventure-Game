//This is for all of our items, it will function in the same way that Collection
//did in our cardGame where it contains an instance of all item objects, all other
//inventories use these objects.
#ifndef ITEMCOLLECTION_H
#define ITEMCOLLECTION_H

#include <string>
#include "Inventory.hpp"
class ItemCollection {
    private:
        Inventory collection;
    
    public:
        ItemCollection();
        ~ItemCollection();
        Item* getSpecificItem(std::string name);
};
#endif
