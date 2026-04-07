#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "Item.hpp"
#include "Player.hpp"
#include "WorldMap.hpp"

TEST(TestPlayer, startsWithDefaultStats) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    EXPECT_EQ(player.getHealth(), 100);
    EXPECT_EQ(player.getHunger(), 100);
    EXPECT_EQ(player.getAttack(), 1);
    EXPECT_EQ(player.getWeapon(), "Fist");

    delete loc;
}

TEST(TestPlayer, startsAtRequestedLocation) {
    WorldMap* map = new WorldMap();
    Player player(map->getLocation(2));

    EXPECT_EQ(player.getCurrent(), map->getLocation(2));

    delete map;
}

TEST(TestPlayer, takeDamageReducesHealth) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.takeDamage(30);

    std::cout.rdbuf(origStream);

    std::string str = "Current player\033[0;31m"
                      " health \033[0mis 70\n";

    EXPECT_EQ(player.getHealth(), 70);
    EXPECT_EQ(tempStream.str(), str);

    delete loc;
}

TEST(TestPlayer, takeDamageDoesNotDropBelowZero) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.takeDamage(150);

    std::cout.rdbuf(origStream);

    std::string str = "Current player\033[0;31m"
                      " health \033[0mis 0\n";

    EXPECT_EQ(player.getHealth(), 0);
    EXPECT_EQ(tempStream.str(), str);

    delete loc;
}

TEST(TestPlayer, takeDamageDoesNotGoAboveHundred) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.takeDamage(-50);

    std::cout.rdbuf(origStream);

    std::string str = "Current player\033[0;31m"
                      " health \033[0mis 100\n";

    EXPECT_EQ(player.getHealth(), 100);
    EXPECT_EQ(tempStream.str(), str);

    delete loc;
}

TEST(TestPlayer, eatIncreasesHungerUpToMax100) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.eat(-30);
    player.eat(50);

    std::cout.rdbuf(origStream);

    std::string str = "Current player\033[0;32m"
                      " hunger \033[0mis 70\n"
                      "Current player\033[0;32m"
                      " hunger \033[0mis 100\n";

    EXPECT_EQ(player.getHunger(), 100);
    EXPECT_EQ(tempStream.str(), str);

    delete loc;
}

TEST(TestPlayer, eatDoesNotDropHungerBelowZero) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.eat(-150);

    std::cout.rdbuf(origStream);

    std::string str = "Current player\033[0;32m"
                      " hunger \033[0mis 0\n";

    EXPECT_EQ(player.getHunger(), 0);
    EXPECT_EQ(tempStream.str(), str);

    delete loc;
}

TEST(TestPlayer, moveActionUpdatesLocationWhenValid) {
    WorldMap map;
    Player player(map.getLocation(0));
    bool valid = false;

    valid = player.moveAction("right", &map);

    EXPECT_TRUE(valid);
    EXPECT_EQ(player.getCurrent(), map.getLocation(1));
}

TEST(TestPlayer, moveActionLeavesLocationWhenInvalidMoveAttempted) {
    WorldMap map;
    Player player(map.getLocation(0));
    bool valid = true;

    valid = player.moveAction("up", &map);

    EXPECT_FALSE(valid);
    EXPECT_EQ(player.getCurrent(), map.getLocation(0));
}

TEST(TestPlayer, setAttackUpdatesAttackValue) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    player.setAttack(12);

    EXPECT_EQ(player.getAttack(), 12);

    delete loc;
}

TEST(TestPlayer, setWeaponUpdatesWeapon) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);
    Weapon* sword = new Weapon("Sword", 10);

    player.setWeapon(sword);

    EXPECT_EQ(player.getWeapon(), "Sword");

    delete sword;
    delete loc;
}

TEST(TestPlayer, addItemIncreasesInventorySize) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);
    int startSize = player.inventorySize();

    player.addItem(new Material("Apple"));

    EXPECT_EQ(player.inventorySize(), startSize + 1);
    EXPECT_TRUE(player.getInventory()->hasName("Apple", 1));

    delete loc;
}

TEST(TestPlayer, removeItemRemovesMatchingItem) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    Item* item = new Material("Stone");

    player.addItem(item);
    int sizeBefore = player.inventorySize();

    player.removeItem(item);

    EXPECT_EQ(player.inventorySize(), sizeBefore - 1);
    EXPECT_FALSE(player.getInventory()->hasName("Stone", 1));

    delete loc;
    delete item;
}

TEST(TestPlayer, getItemAtReturnsInventoryItem) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    Item* item = new Material("Stone");

    player.addItem(item);

    EXPECT_EQ(player.getItemAt(0)->getName(), "Pocket lint");
    EXPECT_EQ(player.getItemAt(player.inventorySize() - 1)->getName(), "Stone");

    delete loc;
}

TEST(TestPlayer, startsWithAtLeastOneItem) {
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    EXPECT_GE(player.inventorySize(), 1);

    delete loc;
}
