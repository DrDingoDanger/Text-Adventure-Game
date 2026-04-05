#include "gtest/gtest.h"
#include "CraftingRecipe.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

TEST(TestCraftingRecipe, canCraftReturnsTrueWhenInputsExist) {
    std::vector<std::string> cost;
    std::vector<CraftingRecipe*> testRecipe;
    Inventory* inv = new Inventory();

    cost.push_back("Wood");
    cost.push_back("Stone");

    testRecipe.push_back(new CraftingRecipe(cost,
        new Material("Piss")));

    inv->add(new Material("Wood"), 1);
    inv->add(new Material("Stone"), 1);

    EXPECT_TRUE(testRecipe[0]->canCraft(inv));

    delete testRecipe[0];
    delete inv;
}

TEST(TestCraftingRecipe, canCraftReturnsFalseWhenInputsMissing) {
    std::vector<std::string> cost;
    std::vector<CraftingRecipe*> testRecipe;
    Inventory* inv = new Inventory();
    std::stringstream tempStream;

    cost.push_back("Bark");
    cost.push_back("Cobble");

    testRecipe.push_back(new CraftingRecipe(cost,
        new Material("Piss")));

    inv->add(new Material("Wood"), 1);
    inv->add(new Material("Stone"), 1);

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    EXPECT_FALSE(testRecipe[0]->canCraft(inv));

    std::cout.rdbuf(origStream);

    std::string str = "You need 1 Bark for this\n"
                      "You need 1 Cobble for this\n";

    EXPECT_EQ(tempStream.str(), str);

    delete testRecipe[0];
    delete inv;
}

TEST(TestCraftingRecipe, canCraftReturnsTrueWhenPlayerHasMoreThanNeeded) {
    std::vector<std::string> cost;
    std::vector<CraftingRecipe*> testRecipe;
    Inventory* inv = new Inventory();

    cost.push_back("Wood");
    cost.push_back("Stone");

    testRecipe.push_back(new CraftingRecipe(cost,
        new Material("Piss")));

    inv->add(new Material("Wood"), 1);
    inv->add(new Material("Wood"), 1);
    inv->add(new Material("Stone"), 1);
    inv->add(new Material("Stone"), 1);

    EXPECT_TRUE(testRecipe[0]->canCraft(inv));

    delete testRecipe[0];
    delete inv;
}

TEST(TestCraftingRecipe, canCraftIgnoresUnrelatedItems) {
    std::vector<std::string> cost;
    std::vector<CraftingRecipe*> testRecipe;
    Inventory* inv = new Inventory();

    cost.push_back("Wood");
    cost.push_back("Stone");

    testRecipe.push_back(new CraftingRecipe(cost,
        new Material("Piss")));

    inv->add(new Material("Wood"), 1);
    inv->add(new Material("Stone"), 1);
    inv->add(new Material("Pizza"), 1);
    inv->add(new Material("Spagete"), 1);

    EXPECT_TRUE(testRecipe[0]->canCraft(inv));

    delete testRecipe[0];
    delete inv;
}

TEST(TestCraftingRecipe, getOutputReturnExpectedItem) {
    std::vector<std::string> cost;
    std::vector<CraftingRecipe*> testRecipe;
    Inventory* inv = new Inventory();

    cost.push_back("Wood");
    cost.push_back("Stone");

    testRecipe.push_back(new CraftingRecipe(cost,
        new Material("Piss")));

    EXPECT_EQ(testRecipe[0]->getOutput()->getName(), "Piss");
    EXPECT_EQ(testRecipe[0]->getOutput()->getType(), "material");

    delete testRecipe[0];
    delete inv;
}

TEST(TestCraftingRecipe, getOutputReturnCorrectPointer) {
    std::vector<std::string> cost;
    std::vector<CraftingRecipe*> testRecipe;
    Inventory* inv = new Inventory();
    Item* temp = new Material("Piss");

    cost.push_back("Wood");
    cost.push_back("Stone");

    testRecipe.push_back(new CraftingRecipe(cost,
        temp));

    EXPECT_EQ(testRecipe[0]->getOutput(), temp);

    delete testRecipe[0];
    delete inv;
}
