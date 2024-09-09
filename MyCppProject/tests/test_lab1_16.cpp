#include <gtest/gtest.h>
#include "../include/lab1_16.h"

// Тест для функции Add
TEST(AdditionTest, PositiveNumbers) {
    EXPECT_EQ(NOD(36, 64), 4);
    EXPECT_EQ(NOD(231, 546), 21);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}