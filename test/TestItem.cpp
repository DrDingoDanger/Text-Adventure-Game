#include "gtest/gtest.h"
#include "Item.hpp"

TEST(TestItem, materialStoresNameAndType) {
    Material item("Coal");

    EXPECT_EQ(item.getName(), "Coal");
    EXPECT_EQ(item.getType(), "material");
}

TEST(TestItem, foodStoresNameTypeAndHunger) {
    Food item("Apple", 5);

    EXPECT_EQ(item.getName(), "Apple");
    EXPECT_EQ(item.getType(), "food");
    EXPECT_EQ(item.getHunger(), 5);
}

TEST(TestItem, foodSetHungerUpdatesValue) {
    Food item("Apple", 5);
    item.setHunger(12);

    EXPECT_EQ(item.getHunger(), 12);
}

TEST(TestItem, weaponStoresNameAndType) {
    Weapon item("Sword", 3);

    EXPECT_EQ(item.getName(), "Sword");
    EXPECT_EQ(item.getType(), "weapon");
    EXPECT_EQ(item.getPower(), 3);
}
