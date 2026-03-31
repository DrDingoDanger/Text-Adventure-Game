#include "gtest/gtest.h"
#include "Location.hpp"
#include "WorldMap.hpp"
#include "Inventory.hpp"
#include "CraftingRecipe.hpp"
#include "NPC.hpp"
#include "Item.hpp"

TEST(TestLocation, constructionTest) {
    //STUB : IDK
}

TEST(TestLocation, storesNameTest) {
    //STUB : Added
    Inventory inv; 

    Location* loc = new Mountain("Name", {}, {}, {}, inv);

    EXPECT_EQ(loc->getName(), "Name");
}

TEST(TestLocation, storesRecipeTest) {
    //STUB : Added
    Inventory inv;
    std::vector<CraftingRecipe*> trades;
    std::vector<std::string> emeraldCost;

    emeraldCost.push_back("Apple");
    trades.push_back(new CraftingRecipe(emeraldCost, new Material("Emerald")));
    trades.push_back(new CraftingRecipe(emeraldCost, new Material("Stick")));

    Location* loc = new Mountain("Name", {}, trades, {}, inv);

    EXPECT_NE(loc->getRecipe(0)->getOutput()->getName(), "Stick");
    EXPECT_EQ(loc->getRecipe(1)->getOutput()->getName(), "Stick");
    EXPECT_EQ(loc->getRecipe(2), nullptr);
}

TEST(TestLocation, storesNPCTest) {
    //STUB : Added
    Inventory inv; 
    std::vector<NPC*> npcs;

    HelpNPC* dan = new HelpNPC("dan", {});
    HelpNPC* phil = new HelpNPC("phil", {});

    npcs.push_back(dan);
    npcs.push_back(phil);

    Location* loc = new Mountain("Name", npcs, {}, {}, inv);

    EXPECT_NE(loc->getNPC(0), phil);
    EXPECT_EQ(loc->getNPC(1), phil);
    EXPECT_EQ(loc->getNPC(2), nullptr);
}

TEST(TestLocation, storesMobTest) {
    //STUB : Added
    Inventory inv; 
    std::vector<Mob*> mobs;

    Mob* bob = new Mob("bob", 5, 1, inv);
    Mob* mike = new Mob("mike", 5, 1, inv);
    
    mobs.push_back(bob);
    mobs.push_back(mike);

    Location* loc = new Mountain("Name", {}, {}, mobs, inv);

    EXPECT_NE(loc->getMob(0), mike);
    EXPECT_EQ(loc->getMob(1), mike);
    EXPECT_EQ(loc->getMob(2), nullptr);
}

TEST(TestLocation, storesInventoryTest) {
    //STUB : Added
    Inventory inv; 
    
    inv.add(new Food("Apple", 3), 1);
    inv.add(new Material("Diamond"), 2);

    Location* loc = new Mountain("Name", {}, {}, {}, inv);

    EXPECT_EQ(loc->getInventory().hasName("Apple", 1), 1);
    EXPECT_EQ(loc->getInventory().hasName("Diamond", 1), 1);
    EXPECT_NE(loc->getInventory().hasName("Stick", 1), 1);
}

TEST(TestLocation, canExitTest) {
    //STUB : Added
    WorldMap* map = new WorldMap();
    Location* loc;

    loc = map->updateLocation("down", loc);
    loc = map->updateLocation("right", loc);

    EXPECT_TRUE(loc->canExit("right", map));
    EXPECT_TRUE(loc->canExit("down", map));
    EXPECT_TRUE(loc->canExit("up", map));
    EXPECT_TRUE(loc->canExit("left", map));
}

TEST(TestLocation, cannotExitTest) {
    //STUB : Added
    WorldMap* map = new WorldMap();
    Location* loc;

    EXPECT_FALSE(loc->canExit("up", map));
    EXPECT_FALSE(loc->canExit("left", map));

    loc = map->updateLocation("down", loc);
    loc = map->updateLocation("right", loc);
    loc = map->updateLocation("down", loc);
    loc = map->updateLocation("right", loc);

    EXPECT_FALSE(loc->canExit("right", map));
    EXPECT_FALSE(loc->canExit("down", map));
}

TEST(TestLocation, runEncounterTest) {
    //STUB : Hold
}
