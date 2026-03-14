#ifndef CRAFTINGRECIPE_HPP
#define CRAFTINGRECIPE_HPP

#include <vector>
#include "Inventory.hpp"
#include "Item.hpp"

class CraftingRecipe {
 private:
    Inventory inputs;
    Item* output;

 public:
    CraftingRecipe(std::vector<Item*> _inputs, Item* _output);
    ~CraftingRecipe();
    bool canCraft(Inventory _inventory);
    void craft(Inventory _inventory);
};

#endif
