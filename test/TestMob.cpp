#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "Inventory.hpp"
#include "Item.hpp"
#include "Mob.hpp"

TEST(TestMob, storesNameAndAttack) {
    Mob* mob = new Mob("Zombie", 7, 5, new Inventory());

    EXPECT_EQ(mob->getName(), "Zombie");
    EXPECT_EQ(mob->getAttack(), 5);

    delete mob;
}

TEST(TestMob, storesInventory) {
    Inventory* inv = new Inventory();
    inv->add(new Material("Bone"), 1);

    Mob* mob = new Mob("Zombie", 7, 5, inv);

    EXPECT_TRUE(mob->getInventory()->hasName("Bone", 1));

    delete mob;
}

TEST(TestMob, startsAliveWhenHealthPositive) {
    Mob* mob = new Mob("Zombie", 7, 5, new Inventory());

    EXPECT_FALSE(mob->isDead());

    delete mob;
}

TEST(TestMob, takeDamageReducesHealthWithoutKilling) {
    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    Mob* mob = new Mob("Zombie", 10, 5, new Inventory());

    mob->takeDamage(4);
    std::string str = "Current mob"
              "\033[0;31m health "
              "\033[0mis 6\n";

    std::cout.rdbuf(origStream);

    EXPECT_EQ(tempStream.str(), str);
    EXPECT_FALSE(mob->isDead());

    delete mob;
}

TEST(TestMob, takeDamageToZeroKillsMob) {
    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    Mob* mob = new Mob("Zombie", 10, 5, new Inventory());

    mob->takeDamage(10);
    std::string str = "Current mob"
              "\033[0;31m health "
              "\033[0mis 0\n";

    std::cout.rdbuf(origStream);

    EXPECT_EQ(tempStream.str(), str);
    EXPECT_TRUE(mob->isDead());

    delete mob;
}

TEST(TestMob, overkillStillLeavesMobDead) {
    std::stringstream tempStream;
    std::streambuf* origStream = std::cout.rdbuf();
    std::cout.rdbuf(tempStream.rdbuf());

    Mob* mob = new Mob("Zombie", 1, 5, new Inventory());

    mob->takeDamage(10);
    std::string str = "Current mob"
              "\033[0;31m health "
              "\033[0mis 0\n";

    std::cout.rdbuf(origStream);

    EXPECT_EQ(tempStream.str(), str);
    EXPECT_TRUE(mob->isDead());

    delete mob;
}
