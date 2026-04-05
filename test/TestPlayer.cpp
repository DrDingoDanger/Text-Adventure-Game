#include "gtest/gtest.h"
#include "Player.hpp"
#include "WorldMap.hpp"

TEST(TestPlayer, startsWithDefaultStats) {
    Player player(new Terrain("test", {}, {}, {}, new Inventory()));

    EXPECT_EQ(player.getHealth(), 100);
    EXPECT_EQ(player.getHunger(), 100);
}

TEST(TestPlayer, startsAtRequestedLocation) {
    WorldMap* map = new WorldMap();
    Player player(map->getLocation(2));

    EXPECT_EQ(player.getCurrent(), map->getLocation(2));

    delete map;
}

TEST(TestPlayer, takeDamageReducesHealth) {
    Player player(new Terrain("test", {}, {}, {}, new Inventory()));

    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.takeDamage(30);

    std::cout.rdbuf(origStream);

    std::string str = "Current player\033[0;31m"
                      " health \033[0mis 70\n";

    EXPECT_EQ(player.getHealth(), 70);
    EXPECT_EQ(tempStream.str(), str);
}

TEST(TestPlayer, takeDamageDoesNotDropBelowZero) {
    Player player(new Terrain("test", {}, {}, {}, new Inventory()));

    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.takeDamage(150);

    std::cout.rdbuf(origStream);

    std::string str = "Current player\033[0;31m"
                      " health \033[0mis 0\n";

    EXPECT_EQ(player.getHealth(), 0);
    EXPECT_EQ(tempStream.str(), str);
}

TEST(TestPlayer, eatIncreasesHungerUpToMax100) {
    Player player(new Terrain("test", {}, {}, {}, new Inventory()));

    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.eat(-30);
    player.eat(50);

    std::cout.rdbuf(origStream);

    std::string str = "Current player\x1B[0;32m hunger"
                      " \x1B[0mis 70\nCurrent player"
                      "\x1B[0;32m hunger \x1B[0mis 100\n";

    EXPECT_EQ(player.getHunger(), 100);
    EXPECT_EQ(tempStream.str(), str);
}

TEST(TestPlayer, eatDoesNotDropHungerBelowZero) {
    Player player(new Terrain("test", {}, {}, {}, new Inventory()));

    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.eat(-150);

    std::cout.rdbuf(origStream);

    std::string str = "Current player\033[0;32m"
                      " hunger \033[0mis 0\n";

    EXPECT_EQ(player.getHunger(), 0);
    EXPECT_EQ(tempStream.str(), str);
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

TEST(TestPlayer, startsWithAtLeastOneItem) {
    Player player(new Terrain("test", {}, {}, {}, new Inventory()));

    EXPECT_GE(player.inventorySize(), 1);
}
