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

    Item* item = new Material("Wood");

    EXPECT_TRUE(inv.has(item, 1));
    EXPECT_TRUE(inv.has(item, 2));

    delete item;
}

TEST(TestInventory, hasReturnsFalseWhenNotEnoughItemsExist) {
    Inventory inv;

    inv.add(new Material("Wood"), 1);

    Item* item = new Material("Wood");

    EXPECT_FALSE(inv.has(item, 2));

    delete item;
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

    Item* item1 = new Material("Wood");
    Item* item2 = new Material("Wood");
    Item* item3 = new Material("Wood");

    inv.add(item1, 1);
    inv.add(item2, 1);
    inv.add(item3, 1);

    Item* item4 = new Material("Wood");

    inv.remove(item4, 2);

    EXPECT_EQ(inv.size(), 1);
    EXPECT_TRUE(inv.has(item4, 1));
    EXPECT_FALSE(inv.has(item4, 2));

    delete item1;
    delete item2;
    delete item4;
}

TEST(TestInventory, removeOnlyRequestedItemType) {
    Inventory inv;

    Item* item1 = new Material("Wood");
    Item* item2 = new Material("Wood");
    Item* item3 = new Material("Stone");

    inv.add(item1, 1);
    inv.add(item2, 1);
    inv.add(item3, 1);

    Item* item4 = new Material("Wood");
    Item* item5 = new Material("Stone");

    inv.remove(item1, 1);

    EXPECT_EQ(inv.size(), 2);
    EXPECT_TRUE(inv.has(item4, 1));
    EXPECT_TRUE(inv.has(item5, 1));


    delete item1;
    delete item4;
    delete item5;
}

TEST(TestInventory, removeByNameRemovesMatchingItems) {
    Inventory inv;

    Item* item = new Material("Wood");

    inv.add(item, 1);
    inv.add(new Material("Wood"), 1);
    inv.add(new Material("Stone"), 1);

    inv.removeByName("Wood", 1);

    EXPECT_EQ(inv.size(), 2);
    EXPECT_TRUE(inv.hasName("Wood", 1));
    EXPECT_FALSE(inv.hasName("Wood", 2));
    EXPECT_TRUE(inv.hasName("Stone", 1));

    delete item;
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
