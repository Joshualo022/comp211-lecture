#include "gtest/gtest.h"

extern "C" {
#include "math_utils.h"
}

TEST(math, add_positive) { EXPECT_EQ(add(2, 3), 5); }

TEST(math, add_negative) { EXPECT_EQ(add(-2, -3), -5); }
