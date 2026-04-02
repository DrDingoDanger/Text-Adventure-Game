#include "gtest/gtest.h"
#include "Player.hpp"
#include "WorldMap.hpp"

TEST(TestPlayer, startsWithDefaultStats) {
    WorldMap map;
    Player player(map.getLocation(0));

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
    WorldMap map;
    Player player(map.getLocation(0));

    player.takeDamage(30);

    EXPECT_EQ(player.getHealth(), 70);
}

TEST(TestPlayer, takeDamageDoesNotDropBelowZero) {
    WorldMap map;
    Player player(map.getLocation(0));

    player.takeDamage(150);

    EXPECT_EQ(player.getHealth(), 0);
}

TEST(TestPlayer, eatIncreasesHungerUpToMax100) {
    WorldMap map;
    Player player(map.getLocation(0));

    player.eat(-30);
    player.eat(50);

    EXPECT_EQ(player.getHunger(), 100);
}

TEST(TestPlayer, eatDoesNotDropHungerBelowZero) {
    WorldMap map;
    Player player(map.getLocation(0));

    player.eat(-150);

    EXPECT_EQ(player.getHunger(), 0);
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
    WorldMap map;
    Player player(map.getLocation(0));

    EXPECT_GE(player.inventorySize(), 1);
}
