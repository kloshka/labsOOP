#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"

class Pentagon : public Figure {
public:
    Pentagon();
    Pentagon(const Point* points);
    Pentagon(const Pentagon& other);

    Pentagon& operator=(const Figure& other) override;
    bool operator==(const Figure& other) const override;

    Point center() const override;
    std::ostream& print(std::ostream& os) const override;
    std::istream& read(std::istream& is) override;
    operator double() const override;

private:
    Point vertices[5];
};

#endif 