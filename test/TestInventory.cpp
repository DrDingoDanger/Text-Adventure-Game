#include "gtest/gtest.h"
#include "Inventory.hpp"
#include "Item.hpp"

TEST(TestInventory, startsEmpty) {
    Inventory inv;
    EXPECT_EQ(inv.size(), 0);
}

TEST(TestInventory, addSingleItemIncreasesSize) {
    Inventory inv;

    inv.add(new Material("Wood"), 1);

    EXPECT_EQ(inv.size(), 1);
    EXPECT_EQ(inv.get(0)->getName(), "Wood");
}

TEST(TestInventory, addMultipleCopiesIncreasesSize) {
    Inventory inv;

    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Wood"), 1);

    EXPECT_EQ(inv.size(), 3);
}

TEST(TestInventory, hasReturnsTrueWhenEnoughItemsExist) {
    Inventory inv;

    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Wood"), 1);

    EXPECT_TRUE(inv.has(new Material("Wood"), 1));
    EXPECT_TRUE(inv.has(new Material("Wood"), 2));
}

TEST(TestInventory, hasReturnsFalseWhenNotEnoughItemsExist) {
    Inventory inv;

    inv.add(new Material("Wood"), 1);

    EXPECT_FALSE(inv.has(new Material("Wood"), 2));
}

TEST(TestInventory, removeDecreasesSize) {
    Inventory inv;

    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Wood"), 1);

    inv.remove(new Material("Wood"), 2);

    EXPECT_EQ(inv.size(), 1);
    EXPECT_TRUE(inv.has(new Material("Wood"), 1));
    EXPECT_FALSE(inv.has(new Material("Wood"), 2));
}

TEST(TestInventory, removeOnlyRequestedItemType) {
    Inventory inv;

    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Stone"), 1);

    inv.remove(new Material("Wood"), 1);

    EXPECT_EQ(inv.size(), 2);
    EXPECT_TRUE(inv.has(new Material("Wood"), 1));
    EXPECT_TRUE(inv.has(new Material("Stone"), 1));
}
