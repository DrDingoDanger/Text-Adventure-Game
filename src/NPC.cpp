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

ShopNPC::ShopNPC(std::string name, Inventory& items)
    : NPC(name, "shop") {
    for (std::size_t i = 0; i < items.size(); i++) {
        stock.add(items.get(i), 1);
    }
}

ShopNPC::~ShopNPC() {}

void ShopNPC::sellItem(Player& player, Item& item) {
    (void)player;
    stock.remove(&item, 1);
}
