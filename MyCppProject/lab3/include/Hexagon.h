#ifndef HEXAGON_H
#define HEXAGON_H

#include "Figure.h"

class Hexagon : public Figure {
public:
    Hexagon();
    Hexagon(const Point* points);
    Hexagon(const Hexagon& other);

    Hexagon& operator=(const Figure& other) override;
    bool operator==(const Figure& other) const override;

    Point center() const override;
    std::ostream& print(std::ostream& os) const override;
    std::istream& read(std::istream& is) override;
    operator double() const override;

private:
    Point vertices[6];
};

#endif 