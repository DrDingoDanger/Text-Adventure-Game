#include "gtest/gtest.h"
#include "Mob.hpp"
#include "Inventory.hpp"

TEST(TestMob, startsAliveWhenHealthPositive) {
    Inventory* drops = new Inventory();
    Mob mob("Wolf", 10, 3, drops);

    EXPECT_FALSE(mob.isDead());

    delete drops;
}

TEST(TestMob, takeDamageReducesHealthWithoutKilling) {
    Inventory* drops = new Inventory();
    Mob mob("Wolf", 10, 3, drops);

    mob.takeDamage(4);
    std::string str = "Current mob health is 6";

    EXPECT_FALSE(mob.isDead());

    delete drops;
}

TEST(TestMob, takeDamageToZeroKillsMob) {
    Inventory* drops = new Inventory();
    Mob mob("Wolf", 10, 3, drops);

    mob.takeDamage(10);

    EXPECT_TRUE(mob.isDead());

    delete drops;
}

TEST(TestMob, overkillStillLeavesMobDead) {
    Inventory* drops = new Inventory();
    Mob mob("Wolf", 10, 3, drops);

    mob.takeDamage(100);

    EXPECT_TRUE(mob.isDead());

    delete drops;
}
