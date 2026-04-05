#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "UserInput.hpp"

TEST(TestUserInput, moveDirectionAcceptsValidInput) {
    UserInput input;
    std::istringstream fakeIn("left\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    std::string result = input.moveDirection();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_EQ(result, "left");
    EXPECT_EQ(fakeOut.str(), "Enter direction (left, right, up, down): ");
}

TEST(TestUserInput, moveDirectionRejectsInvalidInputThenAcceptsValid) {
    UserInput input;
    std::istringstream fakeIn("north\ndown\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    std::string result = input.moveDirection();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_EQ(result, "down");
    EXPECT_EQ(fakeOut.str(), "Enter direction (left, right, up, down): "
                             "Invalid input. Directions only!\n"
                             "Try again: ");
}

TEST(TestUserInput, limitInputAcceptsValidNumber) {
    UserInput input;
    std::istringstream fakeIn("2\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    int result = input.limitInput(4);

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_EQ(result, 2);
    EXPECT_EQ(fakeOut.str(), "Enter choice: ");
}

TEST(TestUserInput, limitInputRejectsNonNumberThenOutOfRangeThenAcceptsValid) {
    UserInput input;
    std::istringstream fakeIn("abc\n5\n3\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    int result = input.limitInput(4);

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_EQ(result, 3);
    EXPECT_EQ(fakeOut.str(), "Enter choice: "
                             "Invalid input. Numbers only!\n"
                             "Try again: "
                             "Input is not a valid item\n"
                             "Try again: ");
}

TEST(TestUserInput, playerActionAcceptsValidAction) {
    UserInput input;
    std::istringstream fakeIn("7\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    int result = input.playerAction();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_EQ(result, 7);
    EXPECT_EQ(fakeOut.str(), "Enter action number: ");
}

TEST(TestUserInput, playerActionRejectsBadInputThenAcceptsValidAction) {
    UserInput input;
    std::istringstream fakeIn("word\n9\n6\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    int result = input.playerAction();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_EQ(result, 6);
    EXPECT_EQ(fakeOut.str(), "Enter action number: "
                             "Invalid input. Numbers only!\n"
                             "Try again: "
                             "Invalid action. Choose 1-7.\n"
                             "Try again: ");
}

TEST(TestUserInput, yesOrNoAcceptsLowercaseY) {
    UserInput input;
    std::istringstream fakeIn("y\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    char result = input.yesOrNo();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_EQ(result, 'y');
    EXPECT_EQ(fakeOut.str(), "Enter y/n: ");
}

TEST(TestUserInput, yesOrNoRejectsInvalidThenAcceptsUppercaseN) {
    UserInput input;
    std::istringstream fakeIn("x\nN\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    char result = input.yesOrNo();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_EQ(result, 'N');
    EXPECT_EQ(fakeOut.str(), "Enter y/n: "
                             "Invalid input. Characters only!\n"
                             "Try again: ");
}

TEST(TestUserInput, pressEnterDisplaysPromptAndClearSequence) {
    UserInput input;
    std::istringstream fakeIn("\n");
    std::ostringstream fakeOut;

    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    input.pressEnter();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

EXPECT_EQ(fakeOut.str(),
          "Press Enter to continue..."
          "\n----------------------------------------------------"
          "\033[H\033[2J");
}
