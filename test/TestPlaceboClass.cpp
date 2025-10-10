/**
 * @author L Nicole Wilson [n.wilson@uleth.ca]
 * @date 2025-10
 */

#include "PlaceboClass.hpp"

#include "gtest/gtest.h"

TEST(TestPlaceboClass, defaultConstructorTest) {
  PlaceboClass* pc = new PlaceboClass();

  EXPECT_NE(pc, nullptr);

  delete pc;
}
