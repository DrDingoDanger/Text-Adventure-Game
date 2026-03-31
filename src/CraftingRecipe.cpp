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

bool CraftingRecipe::canCraft(Inventory* _inventory) {
    std::map<std::string, int> requirements;
    for (const std::string& name : _inputs) {
        requirements[name]++;
    }
    for (const auto& kvp : requirements) {
        const std::string& name = kvp.first;
        int amountNeeded = kvp.second;
        if (!_inventory->hasName(name, amountNeeded)) {
            return false;
        }
    }
    return true;
}

void CraftingRecipe::craft(Inventory* _inventory) {
    if (!canCraft(_inventory)) {
        return;
    }

    // Remove the required items by name
    for (const std::string& name : _inputs) {
        _inventory->removeByName(name, 1);
    }

    // Add the resulting item to the inventory
    _inventory->add(_output, 1);
}
