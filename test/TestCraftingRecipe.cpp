#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "CraftingRecipe.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

TEST(TestCraftingRecipe, canCraftReturnsTrueWhenInputsExist) {
    std::vector<std::string> cost;
    Inventory* inv = new Inventory();

    cost.push_back("Wood");
    cost.push_back("Stone");

    CraftingRecipe* recipe = new CraftingRecipe(cost, new Material("Piss"));

    inv->add(new Material("Wood"), 1);
    inv->add(new Material("Stone"), 1);

    EXPECT_TRUE(recipe->canCraft(inv));

    delete recipe;
    delete inv;
}

TEST(TestCraftingRecipe, canCraftReturnsFalseWhenInputsMissing) {
    std::vector<std::string> cost;
    Inventory* inv = new Inventory();
    std::stringstream tempStream;

    cost.push_back("Bark");
    cost.push_back("Cobble");

    CraftingRecipe* recipe = new CraftingRecipe(cost, new Material("Piss"));

    inv->add(new Material("Wood"), 1);
    inv->add(new Material("Stone"), 1);

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    EXPECT_FALSE(recipe->canCraft(inv));

    std::cout.rdbuf(origStream);

    std::string str = "You need 1 Bark for this\n"
                      "You need 1 Cobble for this\n";

    EXPECT_EQ(tempStream.str(), str);

    delete recipe;
    delete inv;
}

TEST(TestCraftingRecipe, canCraftReturnsTrueWhenPlayerHasMoreThanNeeded) {
    std::vector<std::string> cost;
    Inventory* inv = new Inventory();

    cost.push_back("Wood");
    cost.push_back("Stone");

    CraftingRecipe* recipe = new CraftingRecipe(cost, new Material("Piss"));

    inv->add(new Material("Wood"), 1);
    inv->add(new Material("Wood"), 1);
    inv->add(new Material("Stone"), 1);
    inv->add(new Material("Stone"), 1);

    EXPECT_TRUE(recipe->canCraft(inv));

    delete recipe;
    delete inv;
}

TEST(TestCraftingRecipe, canCraftIgnoresUnrelatedItems) {
    std::vector<std::string> cost;
    Inventory* inv = new Inventory();

    cost.push_back("Wood");
    cost.push_back("Stone");

    CraftingRecipe* recipe = new CraftingRecipe(cost, new Material("Piss"));

    inv->add(new Material("Wood"), 1);
    inv->add(new Material("Stone"), 1);
    inv->add(new Material("Pizza"), 1);
    inv->add(new Material("Spagete"), 1);

    EXPECT_TRUE(recipe->canCraft(inv));

    delete recipe;
    delete inv;
}

TEST(TestCraftingRecipe, canCraftChecksDuplicateInputsProperly) {
    std::vector<std::string> cost;
    Inventory* inv = new Inventory();
    std::stringstream tempStream;

    cost.push_back("Wood");
    cost.push_back("Wood");

    CraftingRecipe* recipe = new CraftingRecipe(cost, new Material("Stick"));

    inv->add(new Material("Wood"), 1);

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    EXPECT_FALSE(recipe->canCraft(inv));

    std::cout.rdbuf(origStream);

    EXPECT_EQ(tempStream.str(), "You need 2 Wood for this\n");

    delete recipe;
    delete inv;
}

TEST(TestCraftingRecipe, getInputsReturnsCorrectVector) {
    std::vector<std::string> cost;

    cost.push_back("Wood");
    cost.push_back("Stone");

    CraftingRecipe* recipe = new CraftingRecipe(cost, new Material("Piss"));

    std::vector<std::string> inputs = recipe->getInputs();

    ASSERT_EQ(inputs.size(), 2);
    EXPECT_EQ(inputs[0], "Wood");
    EXPECT_EQ(inputs[1], "Stone");

    delete recipe;
}

TEST(TestCraftingRecipe, getOutputReturnExpectedItem) {
    std::vector<std::string> cost;

    cost.push_back("Wood");
    cost.push_back("Stone");

    CraftingRecipe* recipe = new CraftingRecipe(cost, new Material("Piss"));

    EXPECT_EQ(recipe->getOutput()->getName(), "Piss");
    EXPECT_EQ(recipe->getOutput()->getType(), "material");

    delete recipe;
}

TEST(TestCraftingRecipe, getOutputReturnCorrectPointer) {
    std::vector<std::string> cost;
    Item* temp = new Material("Piss");

    cost.push_back("Wood");
    cost.push_back("Stone");

    CraftingRecipe* recipe = new CraftingRecipe(cost, temp);

    EXPECT_EQ(recipe->getOutput(), temp);

    delete recipe;
}

TEST(TestCraftingRecipe, craftRemovesInputsAndAddsOutput) {
    std::vector<std::string> cost;
    Inventory* inv = new Inventory();
    std::stringstream tempStream;

    cost.push_back("Wood");
    cost.push_back("Stone");

    Item* item = new Material("Axe");

    CraftingRecipe* recipe = new CraftingRecipe(cost, item);

    inv->add(new Material("Wood"), 1);
    inv->add(new Material("Stone"), 1);

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    recipe->craft(inv);

    std::cout.rdbuf(origStream);

    EXPECT_FALSE(inv->hasName("Wood", 1));
    EXPECT_FALSE(inv->hasName("Stone", 1));
    EXPECT_TRUE(inv->hasName("Axe", 1));

    EXPECT_EQ(tempStream.str(),
              "\n\033[33mAxe\033[0m has been added to you inventory\n");

    inv->removeByName("Axe", 1);

    delete inv;
    delete recipe;
}

TEST(TestCraftingRecipe, craftDoesNothingWhenInputsMissing) {
    std::vector<std::string> cost;
    Inventory* inv = new Inventory();
    std::stringstream tempStream;

    cost.push_back("Wood");
    cost.push_back("Stone");

    CraftingRecipe* recipe = new CraftingRecipe(cost, new Material("Axe"));

    inv->add(new Material("Wood"), 1);

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    recipe->craft(inv);

    std::cout.rdbuf(origStream);

    EXPECT_TRUE(inv->hasName("Wood", 1));
    EXPECT_FALSE(inv->hasName("Stone", 1));
    EXPECT_FALSE(inv->hasName("Axe", 1));

    EXPECT_EQ(tempStream.str(), "You need 1 Stone for this\n");

    delete recipe;
    delete inv;
}
