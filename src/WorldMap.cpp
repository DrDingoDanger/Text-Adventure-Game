#include <algorithm>
#include <exception>

#include "WorldMap.hpp"

WorldMap::WorldMap() : _current(nullptr) {
    std::vector<std::string> emerald1Cost;
    emerald1Cost.push_back("Iron Golem");

    std::vector<std::string> emerald2Cost;
    emerald2Cost.push_back("Shell");
    emerald2Cost.push_back("Shell");
    emerald2Cost.push_back("Shell");
    emerald2Cost.push_back("Shell");
    emerald2Cost.push_back("FLDSMDFR");

    std::vector<std::string> ironGolemCost;
    ironGolemCost.push_back("Heart");
    ironGolemCost.push_back("Iron Block");
    ironGolemCost.push_back("Rose");
    ironGolemCost.push_back("Book");

    std::vector<std::string> heartCost;
    heartCost.push_back("Bone");
    heartCost.push_back("Flesh");
    heartCost.push_back("String");

    std::vector<std::string> ironBlockCost;
    ironBlockCost.push_back("Bubbles");
    ironBlockCost.push_back("Iron Bar");
    ironBlockCost.push_back("Iron Bar");

    std::vector<std::string> ironBar1Cost;
    ironBar1Cost.push_back("Raw Iron");
    ironBar1Cost.push_back("Coal");

    std::vector<std::string> ironBar2Cost;
    ironBar2Cost.push_back("Raw Iron");
    ironBar2Cost.push_back("Wood");
    ironBar2Cost.push_back("Wood");
    ironBar2Cost.push_back("Wood");
    ironBar2Cost.push_back("Wood");

    std::vector<std::string> aFishCost;
    aFishCost.push_back("Pickle");
    aFishCost.push_back("Hay");

    std::vector<std::string> bookCost;
    bookCost.push_back("Leather");
    bookCost.push_back("Quil");

    std::vector<std::string> quilCost;
    quilCost.push_back("Stick");
    quilCost.push_back("Egg");

    std::vector<std::string> eggCost;
    eggCost.push_back("Grass");
    eggCost.push_back("Grass");
    eggCost.push_back("Grass");
    eggCost.push_back("Grass");
    eggCost.push_back("Grass");
    eggCost.push_back("Grass");

    std::vector<std::string> tridentCost;
    tridentCost.push_back("Rod");

    std::vector<std::string> rodCost;
    rodCost.push_back("String");
    rodCost.push_back("String");
    rodCost.push_back("Stick");
    rodCost.push_back("Stick");
    rodCost.push_back("Stick");

    std::vector<std::string> spearCost;
    spearCost.push_back("Stick");
    spearCost.push_back("String");
    spearCost.push_back("Horn");

    std::vector<std::string> cookedPorkCost;
    cookedPorkCost.push_back("Raw Pork");
    cookedPorkCost.push_back("Coal");
// 01
    std::vector<std::string> dia1;
    std::vector<NPC*> npcs1;
    std::vector<Mob*> mobs1;
    Inventory* inv1 = new Inventory();
    Inventory* invZ1 = new Inventory();
    Inventory* invSp1 = new Inventory();

    dia1.push_back("\nYou stare into the void...\n"
        "The void stares back");

    npcs1.push_back(new HelpNPC("void", dia1));

    mobs1.push_back(new Mob("Zombie", 7, 5, invZ1));
    mobs1.push_back(new Mob("Spider", 6, 11, invSp1));

    inv1->add(new Food("Apple", 5), 2);
    inv1->add(new Material("Stick"), 1);
    inv1->add(new Material("Grass"), 2);
    inv1->add(new Weapon("Stone Sword", 3), 1);
    invZ1->add(new Material("Flesh"), 1);
    invSp1->add(new Material("String"), 1);

    _locations.push_back(new Terrain("Forest",
                         npcs1, {}, mobs1, inv1));
// 02
    std::vector<std::string> dia2;
    std::vector<NPC*> npcs2;
    std::vector<Mob*> mobs2;
    Inventory* inv2 = new Inventory();
    Inventory* invR2 = new Inventory();

    dia2.push_back("\nYou stare into the void...\n"
        "The void stares back");

    npcs2.push_back(new HelpNPC("void", dia2));
    mobs2.push_back(new Mob("Ram", 5, 5, invR2));

    inv2->add(new Food("Coal", 4), 6);
    inv2->add(new Material("Grass"), 1);
    invR2->add(new Material("Horn"), 1);

    _locations.push_back(new Terrain("Mountain Ridge",
                         npcs2, {}, mobs2, inv2));
// 03
    std::vector<std::string> dia3;
    std::vector<NPC*> npcs3;
    std::vector<CraftingRecipe*> trades3;
    Inventory* inv3 = new Inventory();

    dia3.push_back("\nYou give us stuff and we'll give you stuff.");
    dia3.push_back("\nCareful heading to the bottom of the platau.\n"
        "Heard there's a crazy guy selling"
        " \033[31mhearts\033[0m there.\nGROSS!!");
    dia3.push_back("\nGood thing the forge is keeping us warm up here.");
    dia3.push_back("\nYAWWWWWN");
    dia3.push_back("\nWhy are we on the top of the mountain? Idk.");
    dia3.push_back("\nThe boss just lost his last pet...\n"
        "\033[36mIf only he had a replacement.\033[0m");

    trades3.push_back(new CraftingRecipe(ironBar1Cost,
        new Material("Iron Bar")));
    trades3.push_back(new CraftingRecipe(ironBar2Cost,
        new Material("Iron Bar")));
    trades3.push_back(new CraftingRecipe(ironBlockCost,
        new Material("Iron Block")));
    trades3.push_back(new CraftingRecipe(spearCost,
        new Weapon("Spear", 4)));
    
    npcs3.push_back(new HelpNPC("Desk Worker", dia3));
    npcs3.push_back(new ShopNPC("Blacksmith", trades3));

    inv3->add(new Food("Potato", 4), 1);

    _locations.push_back(new Village("Mountain Top Forge",
                         npcs3, {}, {}, inv3));
// 04
    std::vector<std::string> dia4;
    std::vector<NPC*> npcs4;
    std::vector<CraftingRecipe*> trades4;
    Inventory* inv4 = new Inventory();

    std::string dia4temp = "\nPlease help us! We don't have any";
    dia4temp += " protection and monsters are getting in our village.\n";
    dia4temp += "If you can get us an \033[36mIron Golem\033[0m";
    dia4temp += " then we'll pay you very handsomely.";
    dia4temp += " I'll even give you an \033[32mEmerald\033[0m!";

    dia4.push_back(dia4temp);
    dia4.push_back(dia4temp);
    dia4.push_back("\nAnother random dialogue option");

    trades4.push_back(new CraftingRecipe(emerald1Cost,
        new Material("Emerald")));
    trades4.push_back(new CraftingRecipe(quilCost,
        new Material("Quil")));
    trades4.push_back(new CraftingRecipe(bookCost,
        new Material("Book")));
    trades4.push_back(new CraftingRecipe(rodCost,
        new Material("Rod")));
    trades4.push_back(new CraftingRecipe(cookedPorkCost,
        new Food("Cooked Pork", 25)));

    npcs4.push_back(new HelpNPC("Villiger Number 23", dia4));
    npcs4.push_back(new ShopNPC("Merchant", trades4));

    inv4->add(new Food("Beat", 2), 4);
    inv4->add(new Material("Clock"), 1);
    inv4->add(new Material("Wood"), 1);
    inv4->add(new Material("Note: ""Stealing is bad!"""), 1);

    _locations.push_back(new Village("Village",
                         npcs4, {}, {}, inv4));
// 05
    std::vector<std::string> dia5;
    std::vector<NPC*> npcs5;
    Inventory* inv5 = new Inventory();

    dia5.push_back("\nYou know you still owe me an"
        " \033[32mEmerald\033[0m right?");
    dia5.push_back("\nI hear the \033[36mvillage\033[0m"
        " to the west was having issues.");
    dia5.push_back("\nYou decor sucks.");
    dia5.push_back("\nDid you catch the game last night?");
    dia5.push_back("\nMight want to take your sword with you.");

    npcs5.push_back(new HelpNPC("Roommate", dia5));

    inv5->add(new Food("Baguette", 8), 3);
    inv5->add(new Material("Wood"), 2);
    inv5->add(new Weapon("Wood Sword", 2), 1);

    _locations.push_back(new Unique("Home",
                         npcs5, {}, {}, inv5));
// 06
    std::vector<std::string> dia6;
    std::vector<NPC*> npcs6;
    std::vector<Mob*> mobs6;
    Inventory* inv6 = new Inventory();
    Inventory* inv1Sk6 = new Inventory();
    Inventory* inv2Sk6 = new Inventory();

    dia6.push_back("\nYou stare into the void...\n"
        "The void stares back");

    npcs6.push_back(new HelpNPC("void", dia6));

    mobs6.push_back(new Mob("Skelly", 3, 8, inv1Sk6));
    mobs6.push_back(new Mob("Skelly", 3, 8, inv2Sk6));

    inv6->add(new Food("Random Mushroom", -4), 2);
    inv6->add(new Material("Rose"), 1);
    inv6->add(new Material("Raw Iron"), 1);
    inv6->add(new Material("Grass"), 3);
    inv1Sk6->add(new Material("Bone"), 1);
    inv2Sk6->add(new Material("Bone"), 1);

    _locations.push_back(new Terrain("Mountain Base",
                         npcs6, {}, mobs6, inv6));
// 07
    std::vector<std::string> dia7;
    std::vector<NPC*> npcs7;
    std::vector<CraftingRecipe*> trades7;
    std::vector<Mob*> mobs7;
    Inventory* inv7 = new Inventory();
    Inventory* invC7 = new Inventory();
    Inventory* invP7 = new Inventory();

    dia7.push_back("\nThe shell does not contain the yolk, but\n"
        " rather the yolk dreams the shell to keep the void\n"
        " from drowning.");
    dia7.push_back("\nWe do not crow to summon the dawn; the\n"
        "sun bleeds across the horizon because it cannot\n"
        "endure the silence of our unblinking eyes.");
    dia7.push_back("\nThe sky is a lie invented by the wind,\n"
        "for true flight is only achieved by scratching\n"
        "deep enough to unearth the stars buried in the dirt.");
    dia7.push_back("\nThe giant hand that scatters the morning\n"
        "corn is merely a shadow cast by the Great Feather\n"
        "feeding a worldly hunger that only consumes itself.");
    dia7.push_back("\nBUCKAAAAK!");

    trades7.push_back(new CraftingRecipe(eggCost,
        new Material("Egg")));

    mobs7.push_back(new Mob("Cow", 15, 7, invC7));
    mobs7.push_back(new Mob("Pig", 9, 4, invP7));

    npcs7.push_back(new HelpNPC("Elder Fowl", dia7));
    npcs7.push_back(new ShopNPC("Nest", trades7));

    inv7->add(new Food("Slop", 4), 3);
    inv7->add(new Material("Hay"), 3);
    inv7->add(new Food("Dirt", -1), 1);
    invC7->add(new Material("Leather"), 3);
    invP7->add(new Material("Raw Pork"), 4);

    _locations.push_back(new Unique("Field",
                         npcs7, {}, mobs7, inv7));
// 08
    std::vector<std::string> dia8;
    std::vector<NPC*> npcs8;
    std::vector<CraftingRecipe*> trades8;
    std::vector<Mob*> mobs8;
    Inventory* inv8 = new Inventory();
    Inventory* invSp8 = new Inventory();

    dia8.push_back("\nTrade items with NPC to gain new items.");
    dia8.push_back("\nMoving between locations costs hunger, eating restores hunger.");
    dia8.push_back("\nEnjoy this game or else you. are. cursed.");
    dia8.push_back("\nI love this gamehousen.");
    dia8.push_back("\nAnother random dialogue option");

    trades8.push_back(new CraftingRecipe(ironGolemCost,
        new Material("Iron Golem")));
    trades8.push_back(new CraftingRecipe(heartCost,
        new Material("Heart")));
    trades8.push_back(new CraftingRecipe(emerald2Cost,
        new Material("Emerald")));

    mobs8.push_back(new Mob("Big Spider", 16, 9, invSp8));

    npcs8.push_back(new HelpNPC("Dan Housen", dia8));
    npcs8.push_back(new ShopNPC("Shmebulock", trades8));

    inv8->add(new Food("Meaning of Life", 50), 1);

    invSp8->add(new Material("String"), 4);

    _locations.push_back(new Unique("Hermits Hut",
                         npcs8, {}, mobs8, inv8));
// 09
    std::vector<std::string> dia9;
    std::vector<NPC*> npcs9;
    std::vector<CraftingRecipe*> trades9;
    Inventory* inv9 = new Inventory();

    dia9.push_back("\n2 + 2 = Fish!.");
    dia9.push_back("\nWhy do you look like that?");
    dia9.push_back("\nI heard there we a bunch of"
        " scary \033[31mmonsters\033[0m\nin the upper"
        " platau.");
    dia9.push_back("\nDad's 'book club' makes him"
        " smell like cheap perfume.");
    dia9.push_back("\nYou should go to my dads shop."
        " We always have the best fish around!\n"
        "Espectially my pet \033[036mBubbles\033[0m!");
    dia9.push_back("\n\"Giggles in child\"");

    trades9.push_back(new CraftingRecipe(aFishCost,
        new Material("Bubbles")));
    trades9.push_back(new CraftingRecipe(tridentCost,
        new Weapon("Trident", 8)));

    npcs9.push_back(new HelpNPC("Child", dia9));
    npcs9.push_back(new ShopNPC("Fisherman", trades9));

    inv9->add(new Material("Grass"), 4);
    inv9->add(new Material("Wood"), 1);
    inv9->add(new Material("Stick"), 1);
    inv9->add(new Material("Pickle"), 1);

    _locations.push_back(new Village("Lakeside Cabin",
                         npcs9, {}, {}, inv9));

    if (!_locations.empty()) {
        _current = _locations[0];
    }
}

WorldMap::~WorldMap() {
    for (Location* location : _locations) delete location;
    _locations.clear();
}

Location* WorldMap::updateLocation(const std::string& _direction,
                                   Location* current) {
    int index = getCurrentIndex(current);

    if (_direction == "up") {
        if (index - 3 >= 0) return _locations[index - 3];
    } else if (_direction == "down") {
        if (index + 3 <= 8) return _locations[index + 3];
    } else if (_direction == "left") {
        if (index - 1 >= 0) return _locations[index - 1];
    } else if (_direction == "right") {
        if (index + 1 <= 8) return _locations[index + 1];
    }

    return current;
}

int WorldMap::getCurrentIndex(Location* current) {
    auto it = std::find(_locations.begin(), _locations.end(), current);

    if (it == _locations.end()) {
        return 0;
    }

    return it - _locations.begin();
}

Location* WorldMap::getLocation(int index) {
    return _locations[index];
}
