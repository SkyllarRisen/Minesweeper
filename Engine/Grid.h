#pragma once
#include "Vectors.h"
#include <vector>

template <class T>

class Grid
{
public:

    Grid(const int width, const int height);
    T& At(const Vec2I& v);


private:

    std::vector<T> m_grid;
    const int m_width, m_height;

};

