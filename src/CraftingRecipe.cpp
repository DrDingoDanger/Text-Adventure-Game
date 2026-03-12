#include "CraftingRecipe.hpp"

CraftingRecipe::CraftingRecipe(vector<Item*> _inputs, Item _output) {
    for (int i = 0; i < _inputs.size(); i++) {
        inputs.push_back(_inputs[i]);
    }
    output = _output;
}

CraftingRecipe::~CraftingRecipe() {}

CraftingRecipe::canCraft(Inventory playerInventory) {
    vector<Item*> temp = playerInventory;
    for (Item* req : inputs) {
        auto it = std::find(temp.begin(), temp.end(), req);
        if (it != temp.end()) {
            temp.erase(it);
        } else {
            return false;
        }
    }
    return true;
}

CraftingRecipe::craft(Inventory playerInventory) {
    for (Item* req : inputs) {
        auto it = std::find(playerInventory.begin(),
                            playerInventory.end(), req);
        if (it != playerInventory.end()) {
            playerInventory.erase(it);
        }
    }
    playerInventory.push_back(output);
}
