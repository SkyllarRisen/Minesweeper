#include "Grid.h"
#include <cassert>

template <class T>
Grid<T>::Grid(const int width, const int height)
    :
    m_grid(width*height, T),
    m_width(width),
    m_height(height)
{
}


template <class T>
T& Grid<T>::At(const Vec2I& v)
{
    assert(v[0] < m_width);
    assert(v[1] < m_height);
    return m_grid.at(v[1]*m_width+v[0]);
}