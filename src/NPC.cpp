#include "NPC.hpp"
#include "Player.hpp"

NPC::NPC(std::string name, Location* location) : _name(name), _location(location) {}

NPC::~NPC() {}

HelpNPC::HelpNPC(std::string name, Location* location, std::vector<std::string> dia)
    : NPC(name, location), diaOptions(dia) {}

HelpNPC::~HelpNPC() {}

std::string HelpNPC::giveHint() {
    if (diaOptions.empty()) {
        return "";
    }

    return diaOptions[0];
}

ShopNPC::ShopNPC(std::string name, Location* location, std::vector<Item*> items)
    : NPC(name, location) {
    for (std::size_t i = 0; i < items.size(); i++) {
        stock.add(items[i], 1);
    }
}

ShopNPC::~ShopNPC() {}

void ShopNPC::sellItem(Player& player, Item& item) {
    (void)player;
    stock.remove(&item, 1);
}
