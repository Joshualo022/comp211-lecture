#include <gtest/gtest.h>
extern "C" {
#include "pointer.h"
}
TEST(PointerTest, ValidPointers) {
    int x = 5;
    int y = 7;
    int result = 0;
    int success = addThroughPointers(&x, &y, &result);
    EXPECT_EQ(success, 1);
    EXPECT_EQ(result, 12);
}