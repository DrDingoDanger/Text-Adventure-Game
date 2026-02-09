/**
 * @author L Nicole Wilson [n.wilson@uleth.ca]
 * @date 2025-10
 */

#include "Placebo.hpp"

#include "gtest/gtest.h"

TEST(TestPlacebo, defaultConstructorTest) {
  Placebo* pc = new Placebo();

  EXPECT_EQ(pc->returnPlacebo(), "Placebo-o-o!");
  delete pc;
}
