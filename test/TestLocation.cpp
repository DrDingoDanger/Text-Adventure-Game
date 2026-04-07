#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "CraftingRecipe.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "Location.hpp"
#include "NPC.hpp"
#include "Player.hpp"
#include "WorldMap.hpp"

class DummyLocation : public Location {
 public:
    DummyLocation(std::vector<Mob*> mobs, float rate)
        : Location("Test", {}, {}, mobs, new Inventory(), rate) {}
};

TEST(TestLocation, storesNameTest) {
    Location* loc = new Terrain("Name", {}, {}, {}, new Inventory());

    EXPECT_EQ(loc->getName(), "Name");

    delete loc;
}

TEST(TestLocation, storesRecipeTest) {
    std::vector<CraftingRecipe*> trades;
    std::vector<std::string> emeraldCost;

    emeraldCost.push_back("Apple");
    trades.push_back(new CraftingRecipe(emeraldCost, new Material("Emerald")));
    trades.push_back(new CraftingRecipe(emeraldCost, new Material("Stick")));

    Location* loc = new Terrain("Name", {}, trades, {}, new Inventory());

    EXPECT_NE(loc->getRecipe(0)->getOutput()->getName(), "Stick");
    EXPECT_EQ(loc->getRecipe(1)->getOutput()->getName(), "Stick");

    for (CraftingRecipe* trade : trades) delete trade;
    trades.clear();
    delete loc;
}

TEST(TestLocation, storesNPCTest) {
    std::vector<NPC*> npcs;

    HelpNPC* dan = new HelpNPC("dan", {});
    HelpNPC* phil = new HelpNPC("phil", {});

    npcs.push_back(dan);
    npcs.push_back(phil);

    Location* loc = new Terrain("Name", npcs, {}, {}, new Inventory());

    EXPECT_NE(loc->getNPC(0), phil);
    EXPECT_EQ(loc->getNPC(1), phil);

    delete loc;
}

TEST(TestLocation, numOfNPCTest) {
    std::vector<NPC*> npcs;

    npcs.push_back(new HelpNPC("dan", {}));
    npcs.push_back(new HelpNPC("phil", {}));

    Location* loc = new Terrain("Name", npcs, {}, {}, new Inventory());

    EXPECT_EQ(loc->numOfNPC(), 2);

    delete loc;
}

TEST(TestLocation, storesMobTest) {
    std::vector<Mob*> mobs;

    Mob* bob = new Mob("bob", 5, 1, new Inventory());
    Mob* mike = new Mob("mike", 5, 1, new Inventory());

    mobs.push_back(bob);
    mobs.push_back(mike);

    Location* loc = new Terrain("Name", {}, {}, mobs, new Inventory());

    EXPECT_NE(loc->getMob(0), mike);
    EXPECT_EQ(loc->getMob(1), mike);

    delete loc;
}

TEST(TestLocation, storesInventoryTest) {
    Inventory* inv = new Inventory();

    inv->add(new Food("Apple", 3), 1);
    inv->add(new Material("Diamond"), 1);
    inv->add(new Material("Diamond"), 1);

    Location* loc = new Terrain("Name", {}, {}, {}, inv);

    EXPECT_EQ(loc->getInventory()->hasName("Apple", 1), 1);
    EXPECT_EQ(loc->getInventory()->hasName("Diamond", 1), 1);
    EXPECT_NE(loc->getInventory()->hasName("Stick", 1), 1);

    delete loc;
}

TEST(TestLocation, canExitTest) {
    WorldMap* map = new WorldMap();
    Location* loc = map->getLocation(0);

    loc = map->updateLocation("down", loc);
    loc = map->updateLocation("right", loc);

    EXPECT_TRUE(loc->canExit("right", map));
    EXPECT_TRUE(loc->canExit("down", map));
    EXPECT_TRUE(loc->canExit("up", map));
    EXPECT_TRUE(loc->canExit("left", map));

    delete map;
}

TEST(TestLocation, cannotExitTest) {
    WorldMap* map = new WorldMap();
    Location* loc = map->getLocation(0);

    EXPECT_FALSE(loc->canExit("up", map));
    EXPECT_FALSE(loc->canExit("left", map));

    loc = map->updateLocation("down", loc);
    loc = map->updateLocation("right", loc);
    loc = map->updateLocation("down", loc);
    loc = map->updateLocation("right", loc);

    EXPECT_FALSE(loc->canExit("right", map));
    EXPECT_FALSE(loc->canExit("down", map));

    delete map;
}

TEST(TestLocation, runEncounterPrintsMessageWhenNoMobs) {
    Location* loc = new Terrain("Name", {}, {}, {}, new Inventory());
    Player* player = new Player(loc);
    std::stringstream tempStream;

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    loc->runEncounter(player);

    std::cout.rdbuf(origStream);

    EXPECT_NE(tempStream.str().find("There are no mobs in the area"),
          std::string::npos);

    delete player;
    delete loc;
}

TEST(TestLocation, runEncounterContainsEnemies) {
    Location* loc = new Terrain("Name", {}, {}, {}, new Inventory());
    Player* player = new Player(loc);
    std::stringstream tempStream;

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    loc->runEncounter(player);

    std::cout.rdbuf(origStream);

    EXPECT_NE(tempStream.str().find("There are no mobs in the area"),
          std::string::npos);

    delete player;
    delete loc;
}

TEST(TestLocation, runEncounterDidEncounter) {
    std::vector<Mob*> mobs;

    Mob* bob = new Mob("bob", 5, 1, new Inventory());

    mobs.push_back(bob);

    Location* loc = new DummyLocation(mobs, 2);
    Player* player = new Player(loc);
    std::stringstream tempStream;

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    loc->runEncounter(player);

    EXPECT_NE(tempStream.str().find("Encounter #1"),
        std::string::npos);
    EXPECT_NE(tempStream.str().find(": bob"),
        std::string::npos);
    EXPECT_NE(tempStream.str().find("Fist : 1 dmg"),
        std::string::npos);

    std::cout.rdbuf(origStream);

    delete player;
    delete loc;
}

TEST(TestLocation, runEncounterDidntEncounter) {
    std::vector<Mob*> mobs;

    Mob* bob = new Mob("bob", 5, 1, new Inventory());

    mobs.push_back(bob);

    Location* loc = new DummyLocation(mobs, 0);
    Player* player = new Player(loc);
    std::stringstream tempStream;

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    loc->runEncounter(player);

    std::cout.rdbuf(origStream);

    EXPECT_NE(tempStream.str().find("Encounter #1"),
        std::string::npos);
    EXPECT_NE(tempStream.str().find(": bob"),
        std::string::npos);
    EXPECT_NE(tempStream.str().find("You did not encounter this mob"),
          std::string::npos);

    delete player;
    delete loc;
}

TEST(TestLocation, runEncounterAddsDropLootToInventory) {
    std::vector<Mob*> mobs;
    Inventory* invM = new Inventory();
    invM->add(new Material("Flesh"), 1);

    Mob* bob = new Mob("bob", 1, 1, invM);

    mobs.push_back(bob);

    Location* loc = new DummyLocation(mobs, 1);
    Player* player = new Player(loc);
    std::stringstream tempStream;

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    loc->runEncounter(player);

    std::cout.rdbuf(origStream);

    EXPECT_TRUE(player->getInventory()->hasName("Flesh", 1));

    delete player;
    delete loc;
}
