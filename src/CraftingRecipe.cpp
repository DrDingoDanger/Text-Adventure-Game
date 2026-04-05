#include "CraftingRecipe.hpp"
#include <iostream>

CraftingRecipe::CraftingRecipe(std::vector<std::string> inputs, Item* output)
    : _inputs(inputs), _output(output) {}

CraftingRecipe::~CraftingRecipe() {
    delete _output;
}

std::vector<std::string> CraftingRecipe::getInputs() {
    return _inputs;
}

Item* CraftingRecipe::getOutput() {
    return _output;
}

bool CraftingRecipe::canCraft(Inventory* _inventory) {
    std::map<std::string, int> requirements;
    bool craft = true;

    for (const std::string& name : _inputs) {
        requirements[name]++;
    }
    int numReq = requirements.size();
    int numCurrent = 0;
    for (const auto& kvp : requirements) {
        const std::string& name = kvp.first;
        int amountNeeded = kvp.second;
        if (!_inventory->hasName(name, amountNeeded)) {
                std::cout << "You need "
                        << amountNeeded << " " << name
                        << " for this\n";
                craft = false;
        }

        numCurrent++;
        if (numCurrent == numReq && craft == false) {
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
    std::cout << "\n\033[33m" << _output->getName()
              << "\033[0m"
              << " has been added to you inventory\n";
}
