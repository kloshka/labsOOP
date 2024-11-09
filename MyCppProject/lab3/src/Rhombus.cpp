#include "Rhombus.h"
#include <cmath>
#include <iostream>

Rhombus::Rhombus() {
    for (int i = 0; i < 4; ++i) {
        vertices[i] = Point();
    }
}

Rhombus::Rhombus(const Point* points) {
    for (int i = 0; i < 4; ++i) {
        vertices[i] = points[i];
    }
}

Rhombus::Rhombus(const Rhombus& other) {
    for (int i = 0; i < 4; ++i) {
        vertices[i] = other.vertices[i];
    }
}

Rhombus& Rhombus::operator=(const Figure& other) {
    if (this != &other) {
        const Rhombus* rhombus = dynamic_cast<const Rhombus*>(&other);
        if (rhombus) {
            Figure::operator=(other); 
            for (int i = 0; i < 4; ++i) {
                vertices[i] = rhombus->vertices[i];
            }
        }
    }
    return *this;
}

bool Rhombus::operator==(const Figure& other) const {
    const Rhombus* rhombus = dynamic_cast<const Rhombus*>(&other);
    if (rhombus) {
        for (int i = 0; i < 4; ++i) {
            if (!(vertices[i] == rhombus->vertices[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Point Rhombus::center() const {
    double x = 0.0, y = 0.0;
    for (const auto& vertex : vertices) {
        x += vertex.x;
        y += vertex.y;
    }
    return Point(x / 4, y / 4);
}

std::ostream& Rhombus::print(std::ostream& os) const {
    os << "Rhombus with vertices: ";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.x << ", " << vertex.y << ") ";
    }
    return os;
}

std::istream& Rhombus::read(std::istream& is) {
    std::cout << "Pls input coordinates of the vertices:\n";
    for (auto& vertex : vertices) {
        is >> vertex.x >> vertex.y;
    }
    return is;
}

Rhombus::operator double() const {
    double d1 = std::sqrt(std::pow(vertices[0].x - vertices[2].x, 2) + std::pow(vertices[0].y - vertices[2].y, 2));
    double d2 = std::sqrt(std::pow(vertices[1].x - vertices[3].x, 2) + std::pow(vertices[1].y - vertices[3].y, 2));
    return (d1 * d2) / 2.0;
}