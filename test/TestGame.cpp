#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "Game.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "Location.hpp"
#include "Player.hpp"

TEST(TestGame, GameIsNotOverAtStart) {
    Game game;

    EXPECT_FALSE(game.isOver());
}

TEST(TestGame, CheckWinIsFalseAtStart) {
    Game game;
    Player player(new Terrain("test", {}, {}, {}, new Inventory()));

    EXPECT_FALSE(game.checkWin(&player));
}

TEST(TestGame, CheckLoseIsFalseAtStart) {
    Game game;

    EXPECT_FALSE(game.checkLose());
}

TEST(TestGame, CheckWinIsTrueWhenPlayerHasEmerald) {
    Game game;
    Player player(new Terrain("test", {}, {}, {}, new Inventory()));
    std::stringstream tempStream;

    player.getInventory()->add(new Material("Emerald"), 1);

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    bool result = game.checkWin(&player);

    std::cout.rdbuf(origStream);

    EXPECT_TRUE(result);
    EXPECT_NE(tempStream.str().find("You WIN!"), std::string::npos);
}

TEST(TestGame, CheckLoseIsFalseWhenPlayerHealthAndHungerArePositive) {
    Game game;

    EXPECT_FALSE(game.checkLose());
}

TEST(TestGame, EndGameSetsGameOverTrue) {
    Game game;

    game.endGame();

    EXPECT_TRUE(game.isOver());
}
