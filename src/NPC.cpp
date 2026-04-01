#include "NPC.hpp"
#include "Player.hpp"

NPC::NPC(std::string name, std::string type) : _name(name), _type(type) {}

NPC::~NPC() {}

std::string NPC::getType() {
    return _type;
}

std::string NPC::getName() {
    return _name;
}

HelpNPC::HelpNPC(std::string name, std::vector<std::string> dia)
    : NPC(name, "help"), diaOptions(dia) {}

HelpNPC::~HelpNPC() {}
//HELP NPC WILL RETURN "USEFUL" HINT
std::string HelpNPC::giveHint() {
    if (diaOptions.empty()) {
        return "";
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, diaOptions.size() - 1);
    std::string random = diaOptions[dist(gen)];
    return random;
}
//SHOPNPC WILL MAKE TRADES WITH PLAYER
ShopNPC::ShopNPC(std::string name, std::vector<CraftingRecipe*> trades)
    : _trades(trades), NPC(name, "shop") {}

ShopNPC::~ShopNPC() {
    for (CraftingRecipe* trades : _trades) delete trades;
    _trades.clear();
}

std::vector<CraftingRecipe*>& ShopNPC::getTrades() {
    return _trades;
}
/*
void ShopNPC::sellItem(Player& player, Item& item) {
    (void)player;
    stock.remove(&item, 1);
}*/
