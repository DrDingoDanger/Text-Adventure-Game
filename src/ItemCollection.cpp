#include "ItemCollection.hpp"

ItemCollection::ItemCollection() {
    //we will add every different item we create to collection here
}

ItemCollection::~ItemCollection() {}

Item* ItemCollection::getSpecificItem(std::string name) {
    for(int i = 0; i < collection.size(); i++) {
        temp = collection[i];
        if(name == temp->getName()) {
            return temp;
        }
    }
}