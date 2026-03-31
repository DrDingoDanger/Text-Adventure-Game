#include "gtest/gtest.h"
#include "CraftingRecipe.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include <vector>
#include <string>

TEST(TestCraftingRecipe, canCraftReturnsTrueWhenInputsExist) {
    Material wood("Wood");
    Weapon axe("Axe", 10);

    Inventory inv;
    inv.add(&wood, 2);

    std::vector<std::string> inputs = {"Wood", "Wood"};
    CraftingRecipe recipe(inputs, &axe);

    EXPECT_TRUE(recipe.canCraft(inv));
}

TEST(TestCraftingRecipe, canCraftReturnsFalseWhenInputsMissing) {
    Material wood("Wood");
    Weapon axe("Axe", 10);

    Inventory inv;
    inv.add(&wood, 1);

    std::vector<std::string> inputs = {"Wood", "Wood"};
    CraftingRecipe recipe(inputs, &axe);

    EXPECT_FALSE(recipe.canCraft(inv));
}

TEST(TestCraftingRecipe, canCraftReturnsTrueWhenPlayerHasMoreThanNeeded) {
    Material wood("Wood");
    Weapon axe("Axe", 10);

    Inventory inv;
    inv.add(&wood, 4);

    std::vector<std::string> inputs = {"Wood", "Wood"};
    CraftingRecipe recipe(inputs, &axe);

    EXPECT_TRUE(recipe.canCraft(inv));
}

TEST(TestCraftingRecipe, canCraftIgnoresUnrelatedItems) {
    Material wood("Wood");
    Material stone("Stone");
    Weapon axe("Axe", 10);

    Inventory inv;
    inv.add(&wood, 2);
    inv.add(&stone, 5);

    std::vector<std::string> inputs = {"Wood", "Wood"};
    CraftingRecipe recipe(inputs, &axe);

    EXPECT_TRUE(recipe.canCraft(inv));
}

TEST(TestCraftingRecipe, getOutputReturnsExpectedItem) {
    Material wood("Wood");
    Weapon axe("Axe", 10);

    std::vector<std::string> inputs = {"Wood", "Wood"};
    CraftingRecipe recipe(inputs, &axe);

    EXPECT_EQ(recipe.getOutput()->getName(), "Axe");
    EXPECT_EQ(recipe.getOutput()->getType(), "weapon");
}

TEST(TestCraftingRecipe, getOutputReturnsSamePointer) {
    Material wood("Wood");
    Weapon axe("Axe", 10);

    std::vector<std::string> inputs = {"Wood", "Wood"};
    CraftingRecipe recipe(inputs, &axe);

    EXPECT_EQ(recipe.getOutput(), &axe);
}
