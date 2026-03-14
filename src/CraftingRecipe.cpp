#include "CraftingRecipe.hpp"

CraftingRecipe::CraftingRecipe(std::vector<Item*> _inputs, Item* _output)
    : output(_output) {
    for (std::size_t i = 0; i < _inputs.size(); i++) {
        inputs.add(_inputs[i], 1);
    }
}

CraftingRecipe::~CraftingRecipe() {}

bool CraftingRecipe::canCraft(Inventory _inventory) {
    for (int i = 0; i < inputs.size(); i++) {
        Item* item = inputs.get(i);
        if (_inventory.has(item, 1) < 1) {
            return false;
        }
    }
    return true;
}

void CraftingRecipe::craft(Inventory _inventory) {
    if (!canCraft(_inventory)) {
        return;
    }

    for (int i = 0; i < inputs.size(); i++) {
        _inventory.remove(inputs.get(i), 1);
    }

    _inventory.add(output, 1);
}
