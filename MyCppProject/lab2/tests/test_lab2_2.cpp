#include "../include/lab2_2.h"
#include <gtest/gtest.h>

TEST(HexTest, AddTest) {
    Hex hex1("A");
    Hex hex2("5");
    hex1.add(hex2);
    ASSERT_EQ(hex1.toString(), "F");
}

TEST(HexTest, SubtractTest) {
    Hex hex1("F");
    Hex hex2("5");
    hex1.subtract(hex2);
    ASSERT_EQ(hex1.toString(), "A");
}

TEST(HexTest, ComparisonTest) {
    Hex hex1("A");
    Hex hex2("A");
    ASSERT_TRUE(hex1.isEqual(hex2));
    ASSERT_FALSE(hex1.isGreater(hex2));
    ASSERT_FALSE(hex1.isLess(hex2));
}
