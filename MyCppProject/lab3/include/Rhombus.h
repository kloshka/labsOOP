#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"

class Rhombus : public Figure {
public:
    Rhombus();
    Rhombus(const Point* points);
    Rhombus(const Rhombus& other);

    Rhombus& operator=(const Figure& other) override;
    bool operator==(const Figure& other) const override;

    Point center() const override;
    std::ostream& print(std::ostream& os) const override;
    std::istream& read(std::istream& is) override;
    operator double() const override;

private:
    Point vertices[4];
};

#endif