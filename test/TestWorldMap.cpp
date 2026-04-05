#include "gtest/gtest.h"
#include "WorldMap.hpp"
#include "Location.hpp"
#include "Inventory.hpp"

TEST(TestWorldMap, updateLocationTest) {
    WorldMap* map = new WorldMap();
    Location* loc = new Terrain("Name", {}, {}, {}, new Inventory());

    loc = map->updateLocation("down", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 3);

    loc = map->updateLocation("right", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 4);

    loc = map->updateLocation("up", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 1);

    loc = map->updateLocation("left", loc);
    EXPECT_EQ(map->getCurrentIndex(loc), 0);

    delete map;
}

TEST(TestWorldMap, updateInvalidLocationTest) {
    WorldMap* map = new WorldMap();
    Location* loc = new Terrain("Name", {}, {}, {}, new Inventory());

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
}

TEST(TestWorldMap, getCurrentIndexReturnsZeroForUnknownLocation) {
    WorldMap* map = new WorldMap();
    Location* loc = new Terrain("Unknown", {}, {}, {}, new Inventory());

    EXPECT_EQ(map->getCurrentIndex(loc), 0);

    delete map;
    delete loc;
}

TEST(TestWorldMap, updateLocationReturnsSameLocationForInvalidDirection) {
    WorldMap* map = new WorldMap();
    Location* loc = map->getLocation(4);

    Location* result = map->updateLocation("north", loc);

    EXPECT_EQ(result, loc);
    EXPECT_EQ(map->getCurrentIndex(result), 4);

    delete map;
}

TEST(TestWorldMap, getLocationReturnsCorrectLocations) {
    WorldMap* map = new WorldMap();

    EXPECT_EQ(map->getLocation(0)->getName(), "Forest");
    EXPECT_EQ(map->getLocation(4)->getName(), "Home");
    EXPECT_EQ(map->getLocation(8)->getName(), "Lake");

    delete map;
}
