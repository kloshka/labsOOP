#ifndef ARRAY_H
#define ARRAY_H

#include "Figure.h"

class Array {
public:
    Array();
    ~Array();

    void add(Figure* figure);
    void remove(size_t index);
    Figure* get(size_t index) const;
    size_t size() const;

private:
    Figure** figures;
    size_t capacity;
    size_t count;

    void resize();
};

#endif 