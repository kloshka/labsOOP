#include "Rhombus.h"
#include <gtest/gtest.h>

TEST(RhombusTest, AreaTest) {
    Point points[4] = {Point(0, 0), Point(1, 1), Point(2, 0), Point(1, -1)};
    Rhombus rhombus(points);
    double expectedArea = 2.0;
    EXPECT_DOUBLE_EQ(static_cast<double>(rhombus), expectedArea);
}

TEST(RhombusTest, CenterTest) {
    Point points[4] = {Point(0, 0), Point(1, 1), Point(2, 0), Point(1, -1)};
    Rhombus rhombus(points);
    Point center = rhombus.center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 0.0);
}

TEST(RhombusTest, EqualityTest) {
    Point points1[4] = {Point(0, 0), Point(1, 1), Point(2, 0), Point(1, -1)};
    Point points2[4] = {Point(0, 0), Point(1, 1), Point(2, 0), Point(1, -1)};
    Rhombus rhombus1(points1);
    Rhombus rhombus2(points2);
    EXPECT_TRUE(rhombus1 == rhombus2);
}

TEST(RhombusTest, AssignmentTest) {
    Point points1[4] = {Point(0, 0), Point(1, 1), Point(2, 0), Point(1, -1)};
    Rhombus rhombus1(points1);
    Rhombus rhombus2;
    rhombus2 = rhombus1;
    EXPECT_TRUE(rhombus1 == rhombus2);
}