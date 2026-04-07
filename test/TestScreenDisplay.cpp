#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "CraftingRecipe.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "Location.hpp"
#include "NPC.hpp"
#include "Player.hpp"
#include "ScreenDisplay.hpp"
#include "WorldMap.hpp"

TEST(TestScreenDisplay, titleScreenTest) {
    ScreenDisplay screen;
    std::stringstream out;

    screen.showTitleScreen(out);

    EXPECT_NE(out.str().find("TEXT ADVENTURE"), std::string::npos);
    EXPECT_NE(out.str().find("QUEST FOR THE"), std::string::npos);
    EXPECT_NE(out.str().find("EMERALD"), std::string::npos);
}

TEST(TestScreenDisplay, instructionsTest) {
    ScreenDisplay screen;
    std::stringstream out;

    screen.gameInstructions(out);

    EXPECT_NE(out.str().find("Text-Adventure-Game"), std::string::npos);
    EXPECT_NE(out.str().find("Move"), std::string::npos);
    EXPECT_NE(out.str().find("Quit"), std::string::npos);
}

TEST(TestScreenDisplay, npcTest) {
    ScreenDisplay screen;
    std::stringstream out;
    std::vector<NPC*> npcs;

    npcs.push_back(new HelpNPC("dan", {}));
    npcs.push_back(new HelpNPC("phil", {}));

    Location* loc = new Terrain("Name", npcs, {}, {}, new Inventory());

    screen.displayNPC(out, loc);

    EXPECT_NE(out.str().find("NPCs:"), std::string::npos);
    EXPECT_NE(out.str().find("1. dan"), std::string::npos);
    EXPECT_NE(out.str().find("2. phil"), std::string::npos);

    delete loc;
}

TEST(TestScreenDisplay, defaultMapTest) {
    ScreenDisplay screen;
    std::stringstream out;
    WorldMap map;

    screen.drawMap(out, &map, map.getLocation(0));

    EXPECT_NE(out.str().find("Forest"), std::string::npos);
    EXPECT_NE(out.str().find("Current area: Forest"), std::string::npos);
}

TEST(TestScreenDisplay, newLocationMapTest) {
    ScreenDisplay screen;
    std::stringstream out;
    WorldMap map;

    screen.drawMap(out, &map, map.getLocation(4));

    EXPECT_NE(out.str().find("Home"), std::string::npos);
    EXPECT_NE(out.str().find("Current area: Home"), std::string::npos);
}

TEST(TestScreenDisplay, nullCurrentMapTest) {
    ScreenDisplay screen;
    std::stringstream out;
    WorldMap map;

    screen.drawMap(out, &map, nullptr);

    EXPECT_NE(out.str().find("Current area: Forest"), std::string::npos);
}

TEST(TestScreenDisplay, numDefaultChoiceTest) {
    ScreenDisplay screen;
    std::stringstream out;

    screen.displayAlwaysChoices(out);

    EXPECT_NE(out.str().find("1- Move"), std::string::npos);
    EXPECT_NE(out.str().find("7- Quit"), std::string::npos);
}

TEST(TestScreenDisplay, statsTest) {
    ScreenDisplay screen;
    std::stringstream out;
    WorldMap map;
    Player player(map.getLocation(0));

    screen.displayPlayerStats(out, player);

    EXPECT_NE(out.str().find("Health: 100"), std::string::npos);
    EXPECT_NE(out.str().find("Hunger: 100"), std::string::npos);
}

TEST(TestScreenDisplay, decreaseStatsTest) {
    ScreenDisplay screen;
    std::stringstream out;
    WorldMap map;
    Player player(map.getLocation(0));

    player.takeDamage(20);
    player.eat(-30);

    screen.displayPlayerStats(out, player);

    EXPECT_NE(out.str().find("Health: 80"), std::string::npos);
    EXPECT_NE(out.str().find("Hunger: 70"), std::string::npos);
}

TEST(TestScreenDisplay, increaseStatsTest) {
    ScreenDisplay screen;
    std::stringstream out;
    WorldMap map;
    Player player(map.getLocation(0));

    player.takeDamage(20);
    player.eat(-30);
    player.eat(10);

    screen.displayPlayerStats(out, player);

    EXPECT_NE(out.str().find("Health: 80"), std::string::npos);
    EXPECT_NE(out.str().find("Hunger: 80"), std::string::npos);
}

TEST(TestScreenDisplay, inventoryTest) {
    ScreenDisplay screen;
    std::stringstream out;
    Inventory inv;

    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Stone"), 1);

    screen.displayInventory(out, &inv);

    EXPECT_NE(out.str().find("Inventory:"), std::string::npos);
    EXPECT_NE(out.str().find("Wood"), std::string::npos);
    EXPECT_NE(out.str().find("Stone"), std::string::npos);
}

TEST(TestScreenDisplay, addItemInventoryTest) {
    ScreenDisplay screen;
    std::stringstream out;
    Inventory inv;

    inv.add(new Material("Apple"), 1);
    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Wood"), 1);

    screen.displayInventory(out, &inv);

    EXPECT_NE(out.str().find("Apple"), std::string::npos);
    EXPECT_NE(out.str().find("Wood 2x"), std::string::npos);
}

TEST(TestScreenDisplay, removeItemInventoryTest) {
    ScreenDisplay screen;
    std::stringstream out;
    Inventory inv;

    Item* item1 = new Material("Wood");
    Item* item2 = new Material("Wood");

    inv.add(item1, 1);
    inv.add(item2, 1);
    inv.removeByName("Wood", 1);

    screen.displayInventory(out, &inv);

    EXPECT_NE(out.str().find("Wood"), std::string::npos);
    EXPECT_EQ(out.str().find("Wood 2x"), std::string::npos);

    delete item1;
}

TEST(TestScreenDisplay, tradesTest) {
    ScreenDisplay screen;
    std::stringstream out;
    Inventory inv;
    std::vector<CraftingRecipe*> trades;
    std::vector<std::string> cost;

    cost.push_back("Wood");
    cost.push_back("Stone");

    trades.push_back(new CraftingRecipe(cost, new Material("Axe")));

    screen.displayTrades(out, trades, &inv);

    EXPECT_NE(out.str().find("Trades:"), std::string::npos);
    EXPECT_NE(out.str().find("Wood & Stone for Axe"), std::string::npos);
    EXPECT_NE(out.str().find("Inventory:"), std::string::npos);

    for (CraftingRecipe* recipe : trades) delete recipe;
    trades.clear();
}

TEST(TestScreenDisplay, tradesWithDuplicateInputsTest) {
    ScreenDisplay screen;
    std::stringstream out;
    Inventory inv;
    std::vector<CraftingRecipe*> trades;
    std::vector<std::string> cost;

    cost.push_back("Wood");
    cost.push_back("Wood");
    cost.push_back("Stone");

    trades.push_back(new CraftingRecipe(cost, new Material("Hammer")));

    screen.displayTrades(out, trades, &inv);

    EXPECT_NE(out.str().find("Wood 2x & Stone for Hammer"), std::string::npos);

    for (CraftingRecipe* recipe : trades) delete recipe;
    trades.clear();
}
