#include "gtest/gtest.h"
#include "Item.hpp"

TEST(TestItem, materialStoresNameAndType) {
    Material item("Wood");

    EXPECT_EQ(item.getName(), "Wood");
    EXPECT_EQ(item.getType(), "material");
}

TEST(TestItem, foodStoresNameTypeAndHunger) {
    Food item("Apple", 15);

    EXPECT_EQ(item.getName(), "Apple");
    EXPECT_EQ(item.getType(), "food");
    EXPECT_EQ(item.getHunger(), 15);
}

TEST(TestItem, foodSetHungerUpdatesValue) {
    Food item("Apple", 15);

    item.setHunger(25);

    EXPECT_EQ(item.getHunger(), 25);
}

TEST(TestItem, weaponStoresProperties) {
    Weapon item("Sword", 10);

    EXPECT_EQ(item.getName(), "Sword");
    EXPECT_EQ(item.getType(), "weapon");
    EXPECT_EQ(item.getPower(), 10);
}
