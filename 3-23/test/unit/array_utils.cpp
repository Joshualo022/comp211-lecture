#include "gtest/gtest.h"

extern "C" {
#include "array_utils.h"
}

TEST(array_utils, sum_empty) {
    int arr[] = {};
    EXPECT_EQ(array_sum(arr, 0), 0);
}

TEST(array_utils, sum_positive) {
    int arr[] = {1, 2, 3, 4, 5};
    EXPECT_EQ(array_sum(arr, 5), 15);
}

TEST(array_utils, max_index_basic) {
    int nums[] = {1, 5, 3, 4};
    EXPECT_EQ(array_max_index(nums, 4), 1);
}
TEST(array_utils, max_index_ties_first) {
    int nums[] = {5, 5, 3, 4};
    EXPECT_EQ(array_max_index(nums, 4), 0);
}
TEST(array_utils, max_index_empty) {
    int nums[] = {};
    EXPECT_EQ(array_max_index(nums, 0), -1);
}

TEST(array_utils, clamp_nonnegative_all_positive) {
    int nums[] = {1, 2, 3, 4};
    array_clamp_nonnegative(nums, 4);
    EXPECT_EQ(nums[0], 1);
    EXPECT_EQ(nums[1], 2);
    EXPECT_EQ(nums[2], 3);
    EXPECT_EQ(nums[3], 4);
}