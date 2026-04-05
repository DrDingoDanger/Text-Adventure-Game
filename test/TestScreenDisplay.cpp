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

    want = "\x1B[H\x1B[2J\n               --"
           " \x1B[0;36mText-Adventure-Game\x1B[0m"
           " --\n\nEnter the requested information"
           " to navigate through the game.\n\n -"
           "\x1B[0;32mMove\x1B[0m: \x1B[4;36mChange"
           " location\x1B[0m by moving left, right,"
           " up, or down.\n -\x1B[0;32mView Inventory"
           "\x1B[0m: Look at the \x1B[4;36mitems in"
           " your inventory\x1B[0m, you are given the"
           " option to use them.\n -\x1B[0;32mView Map"
           "\x1B[0m: View the world map, your "
           "\x1B[4;36mlocation is in brackets\x1B[0m."
           "\n -\x1B[0;32mFind NPC's\x1B[0m: Check"
           " the area for any \x1B[4;36mshop or dialog"
           " NPC's\x1B[0m. NPC's have \x1B[4;36m"
           "mutiple dialog options\x1B[0m and can give"
           " \x1B[4;36mhints\x1B[0m.\n -\x1B[0;32mCheck"
           " Area\x1B[0m: \x1B[4;36mCollect resources"
           "\x1B[0m from the area and \x1B[4;36mfight"
           " mobs for their drops\x1B[0m.\n -\x1B[0;32m"
           "Game Instructions\x1B[0m: View this help"
           " message.\n -\x1B[0;32mQuit\x1B[0m: End"
           " the game.\n\n";

    dis.gameInstructions(have);

    EXPECT_EQ(have.str(), want);
}

TEST(TestScreenDisplay, npcTest) {
    std::stringstream have;
    std::string want;
    ScreenDisplay dis;
    std::string str;
    std::vector<NPC*> npcs;

    npcs.push_back(new HelpNPC("Danhousen", {}));
    dis.displayNPC(have, new Terrain("Name", npcs, {}, {},
                                    new Inventory()));

    want = "\x1B[H\x1B[2J\x1B[0;34mNPCs:"
           "\n\x1B[0m------------------\n"
           "1. Danhousen\n------------------\n";

    EXPECT_EQ(have.str(), want);
}

TEST(TestScreenDisplay, defaultMapTest) {
    std::stringstream have;
    std::string want;
    WorldMap map;
    ScreenDisplay dis;

    want = "\x1B[H\x1B[2J\x1B[2;1H"
           "  [\x1B[0;36mForest\x1B[0m]"
           "   Cliff    Forge\n   Town"
           "    Home    Valley\n   Field"
           "    Hermit    Lake\nCurrent"
           " area: Forest\n\n";

    dis.drawMap(have, &map, map.getLocation(0));

    EXPECT_EQ(have.str(), want);
}

TEST(TestScreenDisplay, newLocationMapTest) {
    std::stringstream have;
    std::string want;
    WorldMap map;
    ScreenDisplay dis;

    want = "\x1B[H\x1B[2J\x1B[2;1H   Forest"
           "   [\x1B[0;36mCliff\x1B[0m]"
           "   Forge\n   Town    Home"
           "    Valley\n   Field    Hermit"
           "    Lake\nCurrent area: Cliff\n\n";

    dis.drawMap(have, &map, map.getLocation(1));

    EXPECT_EQ(have.str(), want);
}

TEST(TestScreenDisplay, numDefaultChoiceTest) {
    std::stringstream have;
    std::string want;
    ScreenDisplay dis;

    want = "What do you want to do?\n"
           "1- Move\n"
           "2- View Inventory\n"
           "3- View Map\n"
           "4- Find NPC's\n"
           "5- Check Area\n"
           "6- Game Instructions\n"
           "7- Quit\n";

    dis.displayAlwaysChoices(have);

    EXPECT_EQ(have.str(), want);
}

TEST(TestScreenDisplay, statsTest) {
    std::stringstream have;
    std::string want;
    WorldMap map;
    ScreenDisplay dis;
    Player player(map.getLocation(0));

    want = "\x1B[0;31mHealth: 100"
           "\n\x1B[0;32mHunger: 100"
           "\n\x1B[0mFist : 1 dmg\n";

    dis.displayPlayerStats(have, player);

    EXPECT_EQ(have.str(), want);
}

TEST(TestScreenDisplay, decreaseStatsTest) {
    std::stringstream have;
    std::string want;
    WorldMap map;
    ScreenDisplay dis;
    Player player(map.getLocation(0));

    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.takeDamage(15);
    player.eat(-5);

    want = "\x1B[0;31mHealth: 85"
           "\n\x1B[0;32mHunger: 95"
           "\n\x1B[0mFist : 1 dmg\n";

    std::string str = "Current player\x1B[0;31m health"
                      " \x1B[0mis 85\nCurrent player"
                      "\x1B[0;32m hunger \x1B[0mis 95\n";

    std::cout.rdbuf(origStream);

    dis.displayPlayerStats(have, player);

    EXPECT_EQ(have.str(), want);
    EXPECT_EQ(tempStream.str(), str);
}

TEST(TestScreenDisplay, increaseStatsTest) {
    std::stringstream have;
    std::string want;
    WorldMap map;
    ScreenDisplay dis;
    Player player(map.getLocation(0));

    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.takeDamage(30);
    player.takeDamage(-10);
    player.eat(-15);
    player.eat(5);

    want = "\x1B[0;31mHealth: 80"
           "\n\x1B[0;32mHunger: 90"
           "\n\x1B[0mFist : 1 dmg\n";

    std::string str = "Current player\x1B[0;31m health"
                      " \x1B[0mis 70\n"
                      "Current player\x1B[0;31m health"
                      " \x1B[0mis 80\n"
                      "Current player\x1B[0;32m hunger"
                      " \x1B[0mis 85\n"
                      "Current player\x1B[0;32m hunger"
                      " \x1B[0mis 90\n";

    std::cout.rdbuf(origStream);

    dis.displayPlayerStats(have, player);

    EXPECT_EQ(have.str(), want);
    EXPECT_EQ(tempStream.str(), str);
}

TEST(TestScreenDisplay, inventoryTest) {
    std::stringstream have;
    std::string want;
    ScreenDisplay dis;
    Inventory* inv = new Inventory();

    inv->add(new Food("Apple", 3), 1);
    inv->add(new Material("Diamond"), 1);
    inv->add(new Material("Diamond"), 1);

    want = "\x1B[0;34mInventory:"
           "\n\x1B[0m------------------\n"
           "1. Apple\n"
           "2. Diamond 2x\n"
           "------------------\n";

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
    inv->add(new Material("Diamond"), 1);
    inv->add(new Material("Diamond"), 1);
    inv->add(new Food("Apple", 3), 1);
    inv->add(new Food("Apple", 3), 1);

    want = "\x1B[0;34mInventory:"
           "\n\x1B[0m------------------\n"
           "1. Apple 3x\n"
           "2. Diamond 2x\n"
           "------------------\n";

    dis.displayInventory(have, inv);

    have.str("");

    inv->add(new Food("Tiddies", 10), 1);

    want = "\x1B[0;34mInventory:"
           "\n\x1B[0m------------------\n"
           "1. Apple 3x\n"
           "2. Diamond 2x\n"
           "3. Tiddies\n"
           "------------------\n";

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
    inv->add(new Material("Diamond"), 1);
    inv->add(new Material("Diamond"), 1);
    inv->add(new Food("Apple", 3), 1);
    inv->add(new Food("Apple", 3), 1);
    inv->add(new Food("Tiddies", 10), 1);

    want = "\x1B[0;34mInventory:"
           "\n\x1B[0m------------------\n"
           "1. Apple 3x\n"
           "2. Diamond 2x\n"
           "3. Tiddies\n"
           "------------------\n";

    dis.displayInventory(have, inv);

    have.str("");

    inv->remove(new Food("Apple", 3), 1);
    inv->remove(new Material("Diamond"), 2);

    want = "\x1B[0;34mInventory:"
           "\n\x1B[0m------------------\n"
           "1. Apple 2x\n"
           "2. Tiddies\n"
           "------------------\n";

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

    want = "\x1B[H\x1B[2J\x1B[0;34mTrades:"
           " \n\x1B[0m------------------\n"
           "1. Apple & Coal for Emerald\n"
           "2. Banana 2x for Chicken\n"
           "------------------\n\n"
           "\x1B[0;34mInventory:"
           "\n\x1B[0m------------------\n"
           "------------------\n";

    dis.displayTrades(have, trades, inv);

    EXPECT_EQ(have.str(), want);

    for (CraftingRecipe* trade : trades) delete trade;
    trades.clear();

    delete inv;
}
