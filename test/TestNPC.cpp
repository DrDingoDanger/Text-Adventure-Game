#include "gtest/gtest.h"
#include "NPC.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

TEST(TestNPC, baseNpcStoresNameAndType) {
    NPC npc("Bob", "generic");

    EXPECT_EQ(npc.getName(), "Bob");
    EXPECT_EQ(npc.getType(), "generic");
}

TEST(TestNPC, helpNpcHasHelpType) {
    std::vector<std::string> hints = {"hint one", "hint two"};
    HelpNPC npc("Guide", hints);

    EXPECT_EQ(npc.getName(), "Guide");
    EXPECT_EQ(npc.getType(), "help");
}

TEST(TestNPC, helpNpcReturnsEmptyStringWhenNoHints) {
    std::vector<std::string> hints;
    HelpNPC npc("Guide", hints);

    EXPECT_EQ(npc.giveHint(), "");
}

TEST(TestNPC, helpNpcReturnsOneOfHints) {
    std::vector<std::string> hints = {"north", "south", "east"};
    HelpNPC npc("Guide", hints);

    std::string result = npc.giveHint();

    EXPECT_TRUE(result == "north" || result == "south" ||
                result == "east");
}

TEST(TestNPC, shopNpcCopiesInventoryIntoStock) {
    Inventory stock;
    Material wood("Wood");
    Food apple("Apple", 4);

    stock.add(&wood, 2);
    stock.add(&apple, 1);

    ShopNPC shop("Trader", stock);

    EXPECT_EQ(shop.getType(), "shop");
    EXPECT_EQ(shop.getInventory().size(), 3);
}
