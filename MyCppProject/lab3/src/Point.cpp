#include "Point.h"

Point::Point() : x(0.0), y(0.0) {}

Point::Point(double xVal, double yVal) : x(xVal), y(yVal) {}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}