#include "gtest/gtest.h"
#include "NPC.hpp"
#include "Item.hpp"
#include "CraftingRecipe.hpp"

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

    EXPECT_TRUE(result == "north" || result == "south" || result == "east");
}

TEST(TestNPC, shopNpcHasShopType) {
    std::vector<CraftingRecipe*> trades;
    ShopNPC shop("Trader", trades);

    EXPECT_EQ(shop.getName(), "Trader");
    EXPECT_EQ(shop.getType(), "shop");
}

TEST(TestNPC, shopNpcReturnsEmptyTradesWhenNoneGiven) {
    std::vector<CraftingRecipe*> trades;
    ShopNPC shop("Trader", trades);

    EXPECT_EQ(shop.getTrades().size(), 0);
}

TEST(TestNPC, shopNpcReturnsTradesVector) {
    std::vector<std::string> cost1;
    std::vector<std::string> cost2;
    std::vector<CraftingRecipe*> trades;

    cost1.push_back("Wood");
    cost2.push_back("Stone");

    CraftingRecipe* recipe1 = new CraftingRecipe(cost1, new Material("Stick"));
    CraftingRecipe* recipe2 = new CraftingRecipe(cost2, new Material("Axe"));

    trades.push_back(recipe1);
    trades.push_back(recipe2);

    ShopNPC shop("Trader", trades);

    EXPECT_EQ(shop.getTrades().size(), 2);
    EXPECT_EQ(shop.getTrades()[0], recipe1);
    EXPECT_EQ(shop.getTrades()[1], recipe2);
    EXPECT_EQ(shop.getTrades()[0]->getOutput()->getName(), "Stick");
    EXPECT_EQ(shop.getTrades()[1]->getOutput()->getName(), "Axe");
}
