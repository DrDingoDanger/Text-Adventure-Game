#include "gtest/gtest.h"
#include "WorldMap.hpp"
#include "Location.hpp"

TEST(TestWorldMap, constructionTest) {
    //STUB : IDK
}

TEST(TestWorldMap, updateLocationTest) {
    //STUB : Added
    WorldMap* map = new WorldMap();
    Location* loc;

    loc = map->updateLocation("down", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 3);

    loc = map->updateLocation("right", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 4);

    loc = map->updateLocation("up", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 1);

    loc = map->updateLocation("left", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 0);
}

TEST(TestWorldMap, updateInvalidLocationTest) {
    //STUB : Added
    WorldMap* map = new WorldMap();
    Location* loc;

    loc = map->updateLocation("up", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 0);

    loc = map->updateLocation("left", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 0);

    loc = map->updateLocation("down", loc);
    loc = map->updateLocation("right", loc);
    loc = map->updateLocation("down", loc);
    loc = map->updateLocation("right", loc);

    loc = map->updateLocation("right", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 8);

    loc = map->updateLocation("down", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 8);
}
