#include "ItemCollection.hpp"

ItemCollection::ItemCollection() {
    //we will add every different item we create to collection here
    //ie; apple = new Food()
    //collection.push_back(apple)
}

ItemCollection::~ItemCollection() {}

Item* ItemCollection::getSpecificItem(std::string name) {
    Item* temp;
    temp = nullptr;
    for (int i = 0; i < collection.size(); i++) {
        temp = collection[i];
        if (name == temp->getName()) {
            return temp;
        }
    }
}
