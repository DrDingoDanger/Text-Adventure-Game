#include "gtest/gtest.h"
#include "Location.hpp"
#include "WorldMap.hpp"
#include "Inventory.hpp"
#include "CraftingRecipe.hpp"
#include "NPC.hpp"
#include "Item.hpp"

TEST(TestLocation, storesNameTest) {
    Inventory* inv = new Inventory();

    Location* loc = new Mountain("Name", {}, {}, {}, inv);

    EXPECT_EQ(loc->getName(), "Name");

    delete loc;
}

TEST(TestLocation, storesRecipeTest) {
    Inventory* inv = new Inventory();
    std::vector<CraftingRecipe*> trades;
    std::vector<std::string> emeraldCost;

    emeraldCost.push_back("Apple");
    trades.push_back(new CraftingRecipe(emeraldCost, new Material("Emerald")));
    trades.push_back(new CraftingRecipe(emeraldCost, new Material("Stick")));

    Location* loc = new Mountain("Name", {}, trades, {}, inv);

    EXPECT_NE(loc->getRecipe(0)->getOutput()->getName(), "Stick");
    EXPECT_EQ(loc->getRecipe(1)->getOutput()->getName(), "Stick");

    delete loc;
}

TEST(TestLocation, storesNPCTest) {
    Inventory* inv = new Inventory();
    std::vector<NPC*> npcs;

    HelpNPC* dan = new HelpNPC("dan", {});
    HelpNPC* phil = new HelpNPC("phil", {});

    npcs.push_back(dan);
    npcs.push_back(phil);

    Location* loc = new Mountain("Name", npcs, {}, {}, inv);

    EXPECT_NE(loc->getNPC(0), phil);
    EXPECT_EQ(loc->getNPC(1), phil);

    delete loc;
}

TEST(TestLocation, storesMobTest) {
    Inventory* inv = new Inventory();
    std::vector<Mob*> mobs;

    Mob* bob = new Mob("bob", 5, 1, inv);
    Mob* mike = new Mob("mike", 5, 1, inv);

    mobs.push_back(bob);
    mobs.push_back(mike);

    Location* loc = new Mountain("Name", {}, {}, mobs, inv);

    EXPECT_NE(loc->getMob(0), mike);
    EXPECT_EQ(loc->getMob(1), mike);

    delete loc;
}

TEST(TestLocation, storesInventoryTest) {
    Inventory* inv = new Inventory();

    inv->add(new Food("Apple", 3), 1);
    inv->add(new Material("Diamond"), 2);

    Location* loc = new Mountain("Name", {}, {}, {}, inv);

    EXPECT_EQ(loc->getInventory()->hasName("Apple", 1), 1);
    EXPECT_EQ(loc->getInventory()->hasName("Diamond", 1), 1);
    EXPECT_NE(loc->getInventory()->hasName("Stick", 1), 1);

    delete loc;
}

TEST(TestLocation, canExitTest) {
    Inventory* inv = new Inventory();
    WorldMap* map = new WorldMap();
    Location* loc = new Mountain("Name", {}, {}, {}, inv);

    loc = map->updateLocation("down", loc);
    loc = map->updateLocation("right", loc);

    EXPECT_TRUE(loc->canExit("right", map));
    EXPECT_TRUE(loc->canExit("down", map));
    EXPECT_TRUE(loc->canExit("up", map));
    EXPECT_TRUE(loc->canExit("left", map));

    delete map;
    delete loc;
}

TEST(TestLocation, cannotExitTest) {
    Inventory* inv = new Inventory();
    WorldMap* map = new WorldMap();
    Location* loc = new Mountain("Name", {}, {}, {}, inv);

    EXPECT_FALSE(loc->canExit("up", map));
    EXPECT_FALSE(loc->canExit("left", map));

    loc = map->updateLocation("down", loc);
    loc = map->updateLocation("right", loc);
    loc = map->updateLocation("down", loc);
    loc = map->updateLocation("right", loc);

    EXPECT_FALSE(loc->canExit("right", map));
    EXPECT_FALSE(loc->canExit("down", map));

    delete map;
    delete loc;
}

TEST(TestLocation, runEncounterTest) {
    //STUB : Hold
}
