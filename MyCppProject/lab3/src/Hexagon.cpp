#include "Hexagon.h"
#include <cmath>
#include <iostream>

Hexagon::Hexagon() {
    for (int i = 0; i < 6; ++i) {
        vertices[i] = Point();
    }
}

Hexagon::Hexagon(const Point* points) {
    for (int i = 0; i < 6; ++i) {
        vertices[i] = points[i];
    }
}

Hexagon::Hexagon(const Hexagon& other) {
    for (int i = 0; i < 6; ++i) {
        vertices[i] = other.vertices[i];
    }
}

Hexagon& Hexagon::operator=(const Figure& other) {
    if (this != &other) {
        const Hexagon* hexagon = dynamic_cast<const Hexagon*>(&other);
        if (hexagon) {
            Figure::operator=(other); 
            for (int i = 0; i < 6; ++i) {
                vertices[i] = hexagon->vertices[i];
            }
        }
    }
    return *this;
}

bool Hexagon::operator==(const Figure& other) const {
    const Hexagon* hexagon = dynamic_cast<const Hexagon*>(&other);
    if (hexagon) {
        for (int i = 0; i < 6; ++i) {
            if (!(vertices[i] == hexagon->vertices[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Point Hexagon::center() const {
    double x = 0.0, y = 0.0;
    for (const auto& vertex : vertices) {
        x += vertex.x;
        y += vertex.y;
    }
    return Point(x / 6, y / 6);
}

std::ostream& Hexagon::print(std::ostream& os) const {
    os << "Hexagon with vertices: ";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.x << ", " << vertex.y << ") ";
    }
    return os;
}

std::istream& Hexagon::read(std::istream& is) {
    std::cout << "Pls input the vertices:\n";
    for (auto& vertex : vertices) {
        is >> vertex.x >> vertex.y;
    }
    return is;
}

Hexagon::operator double() const {
    double area = 0.0;
    for (int i = 0; i < 6; ++i) {
        int j = (i + 1) % 6;
        area += (vertices[i].x * vertices[j].y) - (vertices[j].x * vertices[i].y);
    }
    return std::abs(area) / 2.0;
}