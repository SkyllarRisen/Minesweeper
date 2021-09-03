#pragma once
#include "Vectors.h"
#include <vector>
#include <cassert>

template <class T>

class Grid
{
public:

    Grid(const int width, const int height);
    T& At(const Vec2I& v);
    const T& At(const Vec2I& v) const;
    const std::vector<T>& ListTiles() const;
    int Width() const;
    int Height() const;
private:

    std::vector<T> m_grid;
    const int m_width, m_height;

};

template <class T>
inline 
Grid<T>::Grid(const int width, const int height)
    :
    m_grid(width* height, T()),
    m_width(width),
    m_height(height)
{
}


template <class T>
inline 
T& Grid<T>::At(const Vec2I& v)
{
    assert(v[0] < m_width);
    assert(v[1] < m_height);
    return m_grid.at(v[1] * m_width + v[0]);
}

template<class T>
inline 
const T& Grid<T>::At(const Vec2I& v) const
{
    assert(v[0] < m_width);
    assert(v[1] < m_height);
    return m_grid.at(v[1] * m_width + v[0]);
}

template<class T>
inline 
const std::vector<T>& Grid<T>::ListTiles() const
{
    return m_grid;
}

template<class T>
inline 
int Grid<T>::Width() const
{
    return m_width;
}

template<class T>
inline 
int Grid<T>::Height() const
{
    return m_height;
}

