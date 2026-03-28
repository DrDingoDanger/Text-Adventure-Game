#include "CraftingRecipe.hpp"

CraftingRecipe::CraftingRecipe(std::vector<std::string> inputs, Item* output)
    : _inputs(inputs), _output(output) {}

CraftingRecipe::~CraftingRecipe() {}

std::vector<std::string> CraftingRecipe::getInputs() {
    return _inputs;
}

Item* CraftingRecipe::getOutput() {
    return _output;
}

bool CraftingRecipe::canCraft(Inventory _inventory) {
    for (const std::string& name : _inputs) {
        //Need to make function to return count by name
        //if (!inventoryHasItemByName(_inventory, name)) {
            return false;
        //}
    }
    return true;
}

void CraftingRecipe::craft(Inventory _inventory) {
    if (!canCraft(_inventory)) {
        return;
    }

    for (int i = 0; i < _inputs.size(); i++) {
        //_inventory.remove(inputs.get(i), 1);
    }

    _inventory.add(_output, 1);
}
