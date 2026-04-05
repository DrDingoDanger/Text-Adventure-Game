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

TEST(TestInventory, addKeepsItemsInAlphabeticalOrder) {
    Inventory inv;

    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Apple"), 1);
    inv.add(new Material("Stone"), 1);

    EXPECT_EQ(inv.size(), 3);
    EXPECT_EQ(inv.get(0)->getName(), "Apple");
    EXPECT_EQ(inv.get(1)->getName(), "Stone");
    EXPECT_EQ(inv.get(2)->getName(), "Wood");
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

TEST(TestInventory, hasNameReturnsTrueWhenEnoughItemsExist) {
    Inventory inv;

    inv.add(new Material("Stone"), 1);
    inv.add(new Material("Stone"), 1);

    EXPECT_TRUE(inv.hasName("Stone", 1));
    EXPECT_TRUE(inv.hasName("Stone", 2));
}

TEST(TestInventory, hasNameReturnsFalseWhenItemMissing) {
    Inventory inv;

    inv.add(new Material("Wood"), 1);

    EXPECT_FALSE(inv.hasName("Stone", 1));
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

TEST(TestInventory, removeByNameRemovesMatchingItems) {
    Inventory inv;

    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Stone"), 1);

    inv.removeByName("Wood", 1);

    EXPECT_EQ(inv.size(), 2);
    EXPECT_TRUE(inv.hasName("Wood", 1));
    EXPECT_FALSE(inv.hasName("Wood", 2));
    EXPECT_TRUE(inv.hasName("Stone", 1));
}

TEST(TestInventory, removeByNameDoesNothingWhenItemMissing) {
    Inventory inv;

    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Stone"), 1);

    inv.removeByName("Apple", 1);

    EXPECT_EQ(inv.size(), 2);
    EXPECT_TRUE(inv.hasName("Wood", 1));
    EXPECT_TRUE(inv.hasName("Stone", 1));
}
