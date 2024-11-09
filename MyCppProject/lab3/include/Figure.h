#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include "Point.h"

class Figure {
public:
    virtual ~Figure() = default;

    virtual Point center() const = 0;// геом центр

    virtual std::ostream& print(std::ostream& os) const = 0;
    virtual std::istream& read(std::istream& is) = 0;

    virtual operator double() const = 0; //площадь

    virtual Figure& operator=(const Figure& other) = 0;
    virtual bool operator==(const Figure& other) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
        return figure.print(os);
    }

    friend std::istream& operator>>(std::istream& is, Figure& figure) {
        return figure.read(is);
    }
};

#endif 