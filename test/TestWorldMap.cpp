#include "gtest/gtest.h"
#include "WorldMap.hpp"
#include "Location.hpp"
#include "Inventory.hpp"

TEST(TestWorldMap, updateLocationTest) {
    WorldMap* map = new WorldMap();
    Inventory* inv = new Inventory();
    Location* loc = new Mountain("Name", {}, {}, {}, inv);


    loc = map->updateLocation("down", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 3);

    loc = map->updateLocation("right", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 4);

    loc = map->updateLocation("up", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 1);

    loc = map->updateLocation("left", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 0);

    delete map;
    delete loc;
}

TEST(TestWorldMap, updateInvalidLocationTest) {
    WorldMap* map = new WorldMap();
    Inventory* inv = new Inventory();
    Location* loc = new Mountain("Name", {}, {}, {}, inv);

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

    delete map;
    delete loc;
}
