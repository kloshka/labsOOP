#include "Pentagon.h"

template<Scalar T>
Pentagon<T>::Pentagon() : vertices_(), center_() {}

template<Scalar T>
Pentagon<T>::Pentagon(const std::array<Point<T>, NUM_VERTICES>& vertices) {
    for (size_t i = 0; i < NUM_VERTICES; ++i) {
        vertices_[i] = std::make_unique<Point<T>>(vertices[i]);
    }
    CalculateCenter();
}

template<Scalar T>
Pentagon<T>::Pentagon(const Pentagon& Other) {
    for (size_t i = 0; i < NUM_VERTICES; ++i) {
        vertices_[i] = std::make_unique<Point<T>>(*Other.vertices_[i]);
    }
    center_ = Other.center_;
}

template<Scalar T>
Pentagon<T>::Pentagon(Pentagon&& Other) noexcept {
    vertices_ = std::move(Other.vertices_);
    center_ = std::move(Other.center_);
}

template<Scalar T>
Pentagon<T>::~Pentagon() {}

template<Scalar T>
void Pentagon<T>::CalculateCenter() {
    double area = 0.0;
    T Cx = 0.0;
    T Cy = 0.0;
    for (int i = 0; i < NUM_VERTICES; ++i) {
        int j = (i + 1) % NUM_VERTICES;
        T common = vertices_[i]->getX() * vertices_[j]->getY() - vertices_[j]->getX() * vertices_[i]->getY();
        area += static_cast<double>(common);
        Cx += (vertices_[i]->getX() + vertices_[j]->getX()) * common;
        Cy += (vertices_[i]->getY() + vertices_[j]->getY()) * common;
    }
    area /= 2.0;
    Cx /= (6.0 * area);
    Cy /= (6.0 * area);
    center_.setX(Cx);
    center_.setY(Cy);
}

template<Scalar T>
void Pentagon<T>::Print(std::ostream& os) const {
    os << "Coordinates of the pentagon vertices:\n";
    for (const auto& vertex : vertices_) {
        os << "(" << vertex->getX() << ", " << vertex->getY() << ")\n";
    }
    os << "Center: (" << center_.getX() << ", " << center_.getY() << ")\n";
}

template<Scalar T>
void Pentagon<T>::Read(std::istream& is) {
    std::cout << "Enter the coordinates of the 5 vertices x y\n";
    for (size_t i {0}; i < NUM_VERTICES; ++i) {
        std::cout << "Coordinates of point " << i + 1 << " : ";
        T x, y;
        is >> x >> y;
        vertices_[i] = std::make_unique<Point<T>>(x, y);
    }
    CalculateCenter();
}

template<Scalar T>
double Pentagon<T>::Area() const {
    double area = 0.0;
    for (int i = 0; i < NUM_VERTICES; ++i) {
        int j = (i + 1) % NUM_VERTICES;
        T common = vertices_[i]->getX() * vertices_[j]->getY() - vertices_[j]->getX() * vertices_[i]->getY();
        area += static_cast<double>(common);
    }
    return std::abs(area) / 2.0;
}

template<Scalar T>
Pentagon<T>::operator double() const {
    return Area();
}

template<Scalar T>
Point<T> Pentagon<T>::GetCenter() const {
    return center_;
}

template<Scalar T>
Pentagon<T>& Pentagon<T>::operator=(const Figure<T>& Other) {
    if (this != &Other) {
        try {
            const Pentagon<T>& otherPentagon = dynamic_cast<const Pentagon<T>&>(Other);
            *this = otherPentagon;
        } catch (const std::bad_cast&) {
            // The object is not a Pentagon
            throw std::invalid_argument("Assigned object is not a Pentagon");
        }
    }
    return *this;
}

template<Scalar T>
Pentagon<T>& Pentagon<T>::operator=(const Pentagon<T>& Other) {
    if (this != &Other) {
        // Copy the data
        for (size_t i = 0; i < NUM_VERTICES; ++i) {
            vertices_[i] = std::make_unique<Point<T>>(*Other.vertices_[i]);
        }
        center_ = Other.center_;
    }
    return *this;
}

template<Scalar T>
Pentagon<T>& Pentagon<T>::operator=(Figure<T>&& Other) noexcept {
    if (this != &Other) {
        try {
            Pentagon<T>& otherPentagon = dynamic_cast<Pentagon<T>&>(Other);
            *this = std::move(otherPentagon);
        } catch (const std::bad_cast&) {
            // The object is not a Pentagon
            throw std::invalid_argument("Assigned object is not a Pentagon");
        }
    }
    return *this;
}

template<Scalar T>
Pentagon<T>& Pentagon<T>::operator=(Pentagon<T>&& Other) noexcept {
    if (this != &Other) {
        vertices_ = std::move(Other.vertices_);
        center_ = std::move(Other.center_);
    }
    return *this;
}

template<Scalar T>
bool Pentagon<T>::operator==(const Figure<T>& Other) const {
    if (this != &Other) {
        try {
            const Pentagon<T>& otherPentagon = dynamic_cast<const Pentagon<T>&>(Other);
            for (size_t i {0}; i < NUM_VERTICES; ++i) {
                if (!(*vertices_[i] == *otherPentagon.vertices_[i])) {
                    return false;
                }
            }
        } catch (const std::bad_cast&) {
            // The object is not a Pentagon
            return false;
        }
    }
    return true;
}
