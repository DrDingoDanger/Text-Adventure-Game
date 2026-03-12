#include "NPC.hpp"

NPC::NPC(std::string name, Location location) {
    _name = name;
    _location = location;
}

NPC::~NPC() {}

HelpNPC::HelpNPC(vector<std::string> dia) {
    for (int i = 0; i < dia.size(); i++) {
        diaOptions.push_back(dia[i]);
    }
}

HelpNPC::~HelpNPC() {}

std::string HelpNPC::giveHint() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> distr(0, myVector.size() - 1);
    std::size_t randomIndex = distr(gen);
    ScreenDisplay screen;
    screen.displayHint(std::cout, diaOptions[randomIndex]);
}

ShopNPC::ShopNPC(vector<Item*> items) {
    for (int i = 0; i < item.size(); i++) {
        stock.add(items[i], 1);
    }
}

ShopNPC::~ShopNPC() {}

ShopNPC::buyItem(Item* _item) {
    auto it = std::find(stock.begin(), stock.end(), _item);
    if (it != stock.end()) {
        stock.erase(it);
    }
}
