#ifndef CRAFTINGRECIPE_HPP
#define CRAFTINGRECIPE_HPP

#include <vector>
#include <string>
#include "Inventory.hpp"
#include "Item.hpp"

class CraftingRecipe {
 private:
    std::vector<std::string> _inputs;
    Item* _output;

 public:
    CraftingRecipe(std::vector<std::string> inputs, Item* output);
    ~CraftingRecipe();
    std::vector<std::string> getInputs();
    Item* getOutput();
    bool canCraft(Inventory _inventory);
    void craft(Inventory _inventory);
};

#endif
