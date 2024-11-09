#include "Array.h"

Array::Array() : figures(nullptr), capacity(0), count(0) {}

Array::~Array() {
    for (size_t i = 0; i < count; ++i) {
        delete figures[i];
    }
    delete[] figures;
}

void Array::add(Figure* figure) {
    if (count == capacity) {
        resize();
    }
    figures[count++] = figure;
}

void Array::remove(size_t index) {
    if (index < count) {
        delete figures[index];
        for (size_t i = index; i < count - 1; ++i) {
            figures[i] = figures[i + 1];
        }
        --count;
    }
}

Figure* Array::get(size_t index) const {
    return (index < count) ? figures[index] : nullptr;
}

size_t Array::size() const {
    return count;
}

void Array::resize() {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    Figure** newFigures = new Figure*[capacity];
    for (size_t i = 0; i < count; ++i) {
        newFigures[i] = figures[i];
    }
    delete[] figures;
    figures = newFigures;
}