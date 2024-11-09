#ifndef POINT_H
#define POINT_H

struct Point {
    double x;
    double y;

    Point();
    Point(double xVal, double yVal);

    bool operator==(const Point& other) const;
};

#endif 