#include "gtest/gtest.h"

#include "Game.hpp"
#include "Player.hpp"
#include "Location.hpp"
#include "Inventory.hpp"

TEST(TestGame, GameIsNotOverAtStart) {
    Game game;

    EXPECT_FALSE(game.isOver());
}

TEST(TestGame, CheckWinIsFalseAtStart) {
    Game game;
    Player* player = new Player(new Terrain("test", {}, {}, {},
                                                new Inventory()));

    EXPECT_FALSE(game.checkWin(player));

    delete player;
}

TEST(TestGame, CheckLoseIsFalseAtStart) {
    Game game;

    EXPECT_FALSE(game.checkLose());
}
