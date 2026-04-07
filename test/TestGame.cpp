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
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    EXPECT_FALSE(game.checkWin(&player));

    delete loc;
}

TEST(TestGame, CheckLoseIsFalseAtStart) {
    Game game;
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    EXPECT_FALSE(game.checkLose(&player));

    delete loc;
}

TEST(TestGame, CheckWinIsTrueWhenPlayerHasEmerald) {
    Game game;
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);
    std::stringstream tempStream;

    player.getInventory()->add(new Material("Emerald"), 1);

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    bool result = game.checkWin(&player);

    std::cout.rdbuf(origStream);

    EXPECT_TRUE(result);
    EXPECT_NE(tempStream.str().find("You WIN!"), std::string::npos);

    delete loc;
}

TEST(TestGame, CheckLoseIsFalseWhenPlayerHealthAndHungerArePositive) {
    Game game;
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);

    EXPECT_FALSE(game.checkLose(&player));

    delete loc;
}

TEST(TestGame, CheckLoseIsTrueWhenPlayerHealthisZero) {
    Game game;
    Location* loc = new Terrain("test", {}, {}, {}, new Inventory());
    Player player(loc);
    std::stringstream tempStream;

    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    player.takeDamage(100);

    bool result = game.checkLose(&player);

    std::cout.rdbuf(origStream);

    EXPECT_TRUE(result);
    EXPECT_NE(tempStream.str().find("You Lose >:D"), std::string::npos);

    delete loc;
}

TEST(TestGame, EndGameSetsGameOverTrue) {
    Game game;

    game.endGame();

    EXPECT_TRUE(game.isOver());
}

TEST(TestGame, gameStartAndEnd) {
    Game game;

    std::istringstream fakeIn("\n\n7\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.start();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_TRUE(game.isOver());
}

TEST(TestGame, updateOption1Valid) {
    Game game;
    std::istringstream fakeIn("1\nright\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("Enter direction (left, right, up, down): "),
                std::string::npos);
}

TEST(TestGame, updateOption1Invalid) {
    Game game;
    std::istringstream fakeIn1("1\nright\n\n");
    std::istringstream fakeIn2("1\nright\ndown\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn1.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(fakeIn2.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("You cannot go off the map. Try Again"),
                std::string::npos);
}

TEST(TestGame, updateOption2YesMaterial) {
    Game game;

    std::istringstream fakeIn("2\ny\n1\n\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("Would you like to use an item?"),
                std::string::npos);
    EXPECT_NE(fakeOut.str().find("Enter the items associated number."),
                std::string::npos);
    EXPECT_NE(fakeOut.str().find("Pocket lint material cannot be used."),
                std::string::npos);
}

TEST(TestGame, updateOption2YesFood) {
    Game game;

    std::istringstream fakeIn1("5\ny\n\n");
    std::istringstream fakeIn2("2\ny\n1\n\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn1.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(fakeIn2.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("Current player"), std::string::npos);
    EXPECT_NE(fakeOut.str().find("hunger"), std::string::npos);
    EXPECT_NE(fakeOut.str().find("is 100"), std::string::npos);
}

TEST(TestGame, updateOption2YesWeapon) {
    Game game;

    std::istringstream fakeIn1("5\ny\n\n");
    std::istringstream fakeIn2("2\ny\n4\n\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn1.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(fakeIn2.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("Wood Sword equipped!"), std::string::npos);
}

TEST(TestGame, updateOption2No) {
    Game game;

    std::istringstream fakeIn("2\nn\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("Inventory:"), std::string::npos);
    EXPECT_NE(fakeOut.str().find("1. Pocket lint 2x"), std::string::npos);
}

TEST(TestGame, updateOption3) {
    Game game;

    std::istringstream fakeIn("3\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("Home"), std::string::npos);
    EXPECT_NE(fakeOut.str().find("Current area: Home"), std::string::npos);
}

TEST(TestGame, updateOption4YesHelpNPC) {
    Game game;

    std::istringstream fakeIn("4\ny\n1\n\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("Enter the NPCs associated number."),
                std::string::npos);
}

TEST(TestGame, updateOption4YesShopNPC) {
    Game game;

    std::istringstream fakeIn1("1\nleft\n\n");
    std::istringstream fakeIn2("4\ny\n2\ny\n1\n\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn1.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(fakeIn2.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("Would you like to make a trade?"),
                std::string::npos);
    EXPECT_NE(fakeOut.str().find("Enter the trade's associated number."),
                std::string::npos);
}

TEST(TestGame, updateOption4No) {
    Game game;

    std::istringstream fakeIn("4\nn\n\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("Would you like to interact with an NPC?"),
                std::string::npos);
}

TEST(TestGame, updateOption5Yes) {
    Game game;

    std::istringstream fakeIn1("5\ny\n\n");
    std::istringstream fakeIn2("5\n\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn1.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(fakeIn2.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("There are no more resources in the area"),
                std::string::npos);
}

TEST(TestGame, updateOption5No) {
    Game game;

    std::istringstream fakeIn1("5\nn\n\n\n");
    std::istringstream fakeIn2("5\nn\n\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn1.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(fakeIn2.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("Inventory:"), std::string::npos);
    EXPECT_NE(fakeOut.str().find("Would you like to collect these items?"),
                std::string::npos);
    EXPECT_NE(fakeOut.str().find("There are no mobs in the area"),
                std::string::npos);
}

TEST(TestGame, updateOption6) {
    Game game;

    std::istringstream fakeIn("6\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_NE(fakeOut.str().find("Text-Adventure-Game"), std::string::npos);
    EXPECT_NE(fakeOut.str().find("Move"), std::string::npos);
    EXPECT_NE(fakeOut.str().find("Quit"), std::string::npos);
}

TEST(TestGame, updateOption7) {
    Game game;

    std::istringstream fakeIn("7\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_TRUE(game.isOver());
}

TEST(TestGame, updateOption8) {
    Game game;

    std::istringstream fakeIn("8\n\n7\n\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    game.update();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_EQ(fakeOut.str().find("Invalid input"), std::string::npos);
}
