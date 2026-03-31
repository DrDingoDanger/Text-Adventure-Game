#include "gtest/gtest.h"
#include "Mob.hpp"
#include "Inventory.hpp"

TEST(TestMob, startsAliveWhenHealthPositive) {
    Inventory drops;
    Mob mob("Wolf", 10, 3, drops);

    EXPECT_FALSE(mob.isDead());
}

TEST(TestMob, takeDamageReducesHealthWithoutKilling) {
    Inventory drops;
    Mob mob("Wolf", 10, 3, drops);

    mob.takeDamage(4);

    EXPECT_FALSE(mob.isDead());
}

TEST(TestMob, takeDamageToZeroKillsMob) {
    Inventory drops;
    Mob mob("Wolf", 10, 3, drops);

    mob.takeDamage(10);

    EXPECT_TRUE(mob.isDead());
}

TEST(TestMob, overkillStillLeavesMobDead) {
    Inventory drops;
    Mob mob("Wolf", 10, 3, drops);

    mob.takeDamage(100);

    EXPECT_TRUE(mob.isDead());
}
