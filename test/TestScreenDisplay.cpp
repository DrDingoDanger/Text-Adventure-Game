#include "gtest/gtest.h"
#include "ScreenDisplay.hpp"
#include "Location.hpp"
#include "WorldMap.hpp"
#include "Inventory.hpp"
#include "NPC.hpp"
#include "Player.hpp"

TEST(TestScreenDisplay, instructionsTest) {
    ScreenDisplay dis;
    std::stringstream have;
    std::string want;

    want = "\n-- Text-Adventure-Game --\n";
    want += "Enter the requested information to navigate through the game.\n";
    want += "Move: change location by moving left, right, up, or down.\n";
    want += "viewInv: Look at the items in your inventory,";
    want += "you are given the option to use them.\n";
    want += "viewMap: View the world map, your location is in braces.\n";
    want += "interactNPC: get a list of NPCs in the";
    want += "current location and the ability to interact with them.\n";
    want += "areaResources: Look at all available resources in the";
    want += "location and the option to collect them.\n";
    want += "gameInstructions: View this help message.\n\n";

    dis.gameInstructions(have);

    EXPECT_EQ(have.str(), want);
}

TEST(TestScreenDisplay, npcTest) {
    std::stringstream have;
    std::string want;
    ScreenDisplay dis;
    std::string str;
    Inventory* inv = new Inventory();
    std::vector<NPC*> npcs;
    npcs.push_back(new HelpNPC("Danhousen", {}));
    Location* loc = new Mountain("Name", npcs, {}, {}, inv);

    dis.displayNPC(have, loc);

    want += "NPCs:\n";
    want += "------------------\n";

    for (int i = 0, j = 0; i < 1; i++, j++) {
        str += std::to_string(j);
        str += ". ";
        str += loc->getNPC(i)->getName();
        str += "\n";
    }
    want += str;
    want += "------------------\n";

    EXPECT_EQ(have.str(), want);

    delete loc;
}

TEST(TestScreenDisplay, defaultMapTest) {
    std::stringstream have;
    std::string want;
    WorldMap* map = new WorldMap();
    ScreenDisplay dis;

    want = "[M0]  M1  M2\n";
    want += "F3  F4  F5\n";
    want += "M6  M7  M8\n";

    dis.drawMap(have, map, map->getLocation(0));

    EXPECT_EQ(have.str(), want);

    delete map;
}

TEST(TestScreenDisplay, newLocationMapTest) {
    std::stringstream have;
    std::string want;
    WorldMap* map = new WorldMap();
    ScreenDisplay dis;

    want =  "M0  [M1]  M2\n";
    want += "F3  F4  F5\n";
    want += "M6  M7  M8\n";

    dis.drawMap(have, map, map->getLocation(1));

    EXPECT_EQ(have.str(), want);

    delete map;
}

TEST(TestScreenDisplay, numDefaultChoiceTest) {
    std::stringstream have;
    std::string want;
    ScreenDisplay dis;

    want =  "What do you want to do?\n";
    want += "1- move\n";
    want += "2- viewStats\n";
    want += "3- viewMap\n";
    want += "4- interactNPC\n";
    want += "5- areaResources\n";
    want += "6- gameInstructions\n";

    dis.displayAlwaysChoices(have);

    EXPECT_EQ(have.str(), want);
}

TEST(TestScreenDisplay, statsTest) {
    std::stringstream have;
    std::string want;
    WorldMap* map = new WorldMap();
    ScreenDisplay dis;
    Player player(map->getLocation(0));

    want =  "Health: 100\n";
    want += "Hunger: 100\n";
    want += "Attack: 1\n";

    dis.displayPlayerStats(have, player);

    EXPECT_EQ(have.str(), want);

    delete map;
}

TEST(TestScreenDisplay, decreaseStatsTest) {
    std::stringstream have;
    std::string want;
    WorldMap* map = new WorldMap();
    ScreenDisplay dis;
    bool temp = true;
    Player player(map->getLocation(0));

    player.takeDamage(15);
    player.eat(-5);

    want =  "Health: 85\n";
    want += "Hunger: 95\n";
    want += "Attack: 1\n";

    dis.displayPlayerStats(have, player);

    EXPECT_EQ(have.str(), want);

    delete map;
}

TEST(TestScreenDisplay, increaseStatsTest) {
    std::stringstream have;
    std::string want;
    WorldMap* map = new WorldMap();
    ScreenDisplay dis;
    Player player(map->getLocation(0));

    player.takeDamage(30);
    player.takeDamage(-10);
    player.eat(-15);
    player.eat(5);

    want =  "Health: 80\n";
    want += "Hunger: 90\n";
    want += "Attack: 1\n";

    dis.displayPlayerStats(have, player);

    EXPECT_EQ(have.str(), want);

    delete map;
}

TEST(TestScreenDisplay, inventoryTest) {
    std::stringstream have;
    std::string want;
    ScreenDisplay dis;
    Inventory* inv = new Inventory();

    inv->add(new Food("Apple", 3), 1);
    inv->add(new Material("Diamond"), 2);

    want =  "Inventory:\n";
    want += "------------------\n";
    want += "1. Apple";
    want += "\n";
    want += "2. Diamond 2x";
    want += "\n";
    want += "------------------\n";

    dis.displayInventory(have, inv);

    EXPECT_EQ(have.str(), want);

    delete inv;
}

TEST(TestScreenDisplay, addItemInventoryTest) {
    std::stringstream have;
    std::string want;
    ScreenDisplay dis;
    Inventory* inv = new Inventory();

    inv->add(new Food("Apple", 3), 1);
    inv->add(new Material("Diamond"), 2);
    inv->add(new Food("Apple", 3), 2);
    inv->add(new Food("Tiddies", 10), 1);

    want =  "Inventory:\n";
    want += "------------------\n";
    want += "1. Apple 3x";
    want += "\n";
    want += "2. Diamond 2x";
    want += "\n";
    want += "3. Tiddies";
    want += "\n";
    want += "------------------\n";

    dis.displayInventory(have, inv);

    EXPECT_EQ(have.str(), want);

    delete inv;
}

TEST(TestScreenDisplay, removeItemInventoryTest) {
    std::stringstream have;
    std::string want;
    ScreenDisplay dis;
    Inventory* inv = new Inventory();

    inv->add(new Food("Apple", 3), 1);
    inv->add(new Material("Diamond"), 2);
    inv->add(new Food("Apple", 3), 2);
    inv->add(new Food("Tiddies", 10), 1);

    inv->remove(new Food("Apple", 3), 1);
    inv->remove(new Material("Diamond"), 2);

    want =  "Inventory:\n";
    want += "------------------\n";
    want += "1. Apple 2x";
    want += "\n";
    want += "2. Tiddies";
    want += "\n";
    want += "------------------\n";

    dis.displayInventory(have, inv);

    EXPECT_EQ(have.str(), want);

    delete inv;
}

TEST(TestScreenDisplay, tradesTest) {
    std::stringstream have;
    std::string want;
    ScreenDisplay dis;
    Inventory* inv = new Inventory();
    std::vector<CraftingRecipe*> trades;
    std::vector<std::string> emeraldCost;
    std::vector<std::string> chickenCost;

    emeraldCost.push_back("Apple");
    emeraldCost.push_back("Coal");

    chickenCost.push_back("Banana");
    chickenCost.push_back("Banana");

    trades.push_back(new CraftingRecipe(emeraldCost, new Material("Emerald")));
    trades.push_back(new CraftingRecipe(chickenCost, new Food("Chicken", 2)));

    want =  "Trades: \n";
    want += "------------------\n";
    want += "1. Apple, Coal for Emerald false";
    want += "\n";
    want += "2. Banana, Banana for Chicken false";
    want += "\n";
    want += "------------------\n";

    dis.displayTrades(have, trades, inv);

    EXPECT_EQ(have.str(), want);

    for (CraftingRecipe* trade : trades) delete trade;
    trades.clear();

    delete inv;
}
