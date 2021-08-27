#include "Vectors.h"
#include <cassert>
#include <cmath>
#include <cstdlib>

Vec2D::Vec2D(double x, double y)
    :
    m_x(x),
    m_y(y)
{
}

double& Vec2D::operator[](int index)
{
    assert(index >= 0);
    assert(index <= 1);
    switch (index)
    {
    case 0:
        return m_x;
    case 1:
        return m_y;
    }
}

const double& Vec2D::operator[](const int index) const
{
    assert(index >= 0);
    assert(index <= 1);
    switch (index)
    {
    case 0:
        return m_x;
    case 1:
        return m_y;
    default:
        return std::nan("VEC_INDEX_OOB");
    }
}

Vec2D Vec2D::operator+(const Vec2D& v) const
{
    return Vec2D( (*this)[0] + v[0], (*this)[1] + v[1] );
}

Vec2D& Vec2D::operator+=(const Vec2D& v)
{
    return *this = *this + v;
}

Vec2D Vec2D::operator-(const Vec2D& v) const
{
    return Vec2D((*this)[0] - v[0], (*this)[1] - v[1]);
}

Vec2D& Vec2D::operator-=(const Vec2D& v)
{
    return *this = *this - v;
}

Vec2D Vec2D::operator*(const double n) const
{
    return Vec2D((*this)[0] * n, (*this)[1] * n);
}


Vec2D& Vec2D::operator*=(const double n)
{
    return *this = *this * n;
}

Vec2D Vec2D::operator/(const double n) const
{
    assert(n != 0);
    return Vec2D((*this)[0] / n, (*this)[1] / n);
}

Vec2D& Vec2D::operator/=(const double n)
{

    return *this = *this / n;
}


Vec2D Vec2D::operator-() const
{
    return *this * -1;
}

double Vec2D::operator*(const Vec2D& v) const
{
    return (*this)[0] * v[0] + (*this)[1] * v[1];
}

Vec2D operator*(const double n, const Vec2D& v)
{
    return v * n;
}

Vec2D operator/(const double n, const Vec2D& v)
{
    return v / n;
}

double Vec2D::NormSq() const
{
    return (*this) * (*this);
}

double Vec2D::Norm() const
{
    return sqrt(NormSq());
}

Vec2D Vec2D::Direction() const
{
    if ((*this).NormSq() == 0)
        return *this;
    else
        return (*this) / (*this).Norm();
}

Vec2D& Vec2D::Normalize()
{
    return (*this) = (*this).Direction();
}
