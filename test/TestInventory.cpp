#include "gtest/gtest.h"
#include "Inventory.hpp"
#include "Item.hpp"

TEST(TestInventory, startsEmpty) {
    Inventory inv;
    EXPECT_EQ(inv.size(), 0);
}

TEST(TestInventory, addSingleItemIncreasesSize) {
    Inventory inv;
    Material rock("Rock");

    inv.add(&rock, 1);

    EXPECT_EQ(inv.size(), 1);
    EXPECT_EQ(inv.get(0)->getName(), "Rock");
}

TEST(TestInventory, addMultipleCopiesIncreasesSize) {
    Inventory inv;
    Material rock("Rock");

    inv.add(&rock, 3);

    EXPECT_EQ(inv.size(), 3);
}

TEST(TestInventory, hasReturnsTrueWhenEnoughItemsExist) {
    Inventory inv;
    Material wood("Wood");

    inv.add(&wood, 2);

    EXPECT_TRUE(inv.has(&wood, 1));
    EXPECT_TRUE(inv.has(&wood, 2));
}

TEST(TestInventory, hasReturnsFalseWhenNotEnoughItemsExist) {
    Inventory inv;
    Material wood("Wood");

    inv.add(&wood, 1);

    EXPECT_FALSE(inv.has(&wood, 2));
}

TEST(TestInventory, removeDecreasesSize) {
    Inventory inv;
    Material wood("Wood");

    inv.add(&wood, 3);
    inv.remove(&wood, 2);

    EXPECT_EQ(inv.size(), 1);
    EXPECT_TRUE(inv.has(&wood, 1));
    EXPECT_FALSE(inv.has(&wood, 2));
}

TEST(TestInventory, removeOnlyRequestedItemType) {
    Inventory inv;
    Material wood("Wood");
    Material stone("Stone");

    inv.add(&wood, 2);
    inv.add(&stone, 1);

    inv.remove(&wood, 1);

    EXPECT_EQ(inv.size(), 2);
    EXPECT_TRUE(inv.has(&wood, 1));
    EXPECT_TRUE(inv.has(&stone, 1));
}
