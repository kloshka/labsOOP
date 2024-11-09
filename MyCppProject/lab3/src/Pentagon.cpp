#include "Pentagon.h"
#include <cmath>
#include <iostream>

Pentagon::Pentagon() {
    for (int i = 0; i < 5; ++i) {
        vertices[i] = Point();
    }
}

Pentagon::Pentagon(const Point* points) {
    for (int i = 0; i < 5; ++i) {
        vertices[i] = points[i];
    }
}

Pentagon::Pentagon(const Pentagon& other) {
    for (int i = 0; i < 5; ++i) {
        vertices[i] = other.vertices[i];
    }
}

Pentagon& Pentagon::operator=(const Figure& other) {
    if (this != &other) {
        const Pentagon* pentagon = dynamic_cast<const Pentagon*>(&other);
        if (pentagon) {
            Figure::operator=(other); 
            for (int i = 0; i < 5; ++i) {
                vertices[i] = pentagon->vertices[i];
            }
        }
    }
    return *this;
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* pentagon = dynamic_cast<const Pentagon*>(&other);
    if (pentagon) {
        for (int i = 0; i < 5; ++i) {
            if (!(vertices[i] == pentagon->vertices[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Point Pentagon::center() const {
    double x = 0.0, y = 0.0;
    for (const auto& vertex : vertices) {
        x += vertex.x;
        y += vertex.y;
    }
    return Point(x / 5, y / 5);
}

std::ostream& Pentagon::print(std::ostream& os) const {
    os << "Pentagon with vertices: ";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.x << ", " << vertex.y << ") ";
    }
    return os;
}

std::istream& Pentagon::read(std::istream& is) {
    std::cout << "Pls input coordinates of the vertices:\n";
    for (auto& vertex : vertices) {
        is >> vertex.x >> vertex.y;
    }
    return is;
}

Pentagon::operator double() const {
    double area = 0.0;
    for (int i = 0; i < 5; ++i) {
        int j = (i + 1) % 5;
        area += (vertices[i].x * vertices[j].y) - (vertices[j].x * vertices[i].y);
    }
    return std::abs(area) / 2.0;
}