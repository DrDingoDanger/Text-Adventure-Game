#include <gtest/gtest.h>

#include "Game.hpp"

TEST(TestGame, GameIsNotOverAtStart) {
    Game game;

    EXPECT_FALSE(game.isOver());
}

TEST(TestGame, CheckWinIsFalseAtStart) {
    Game game;

    EXPECT_FALSE(game.checkWin());
}

TEST(TestGame, CheckLoseIsFalseAtStart) {
    Game game;

    EXPECT_FALSE(game.checkLose());
}
