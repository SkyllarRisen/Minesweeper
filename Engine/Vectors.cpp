#include "Vectors.h"
#include <cassert>
#include <cmath>
#include <cstdlib>

double g_errD = std::nan("VEC_INDEX_OOB");

Vec2D::Vec2D()
    :
    m_x(0),
    m_y(0)
{
}

Vec2D::Vec2D(const double x, const double y)
    :
    m_x(x),
    m_y(y)
{
}

double& Vec2D::operator[](const int index)
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
        return g_errD;
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
        return g_errD;
    }
}

Vec2D Vec2D::operator+(const Vec2D& v) const
{
    return Vec2D( 
                    (*this)[0] + v[0], 
                    (*this)[1] + v[1] 
                );
}

Vec2D& Vec2D::operator+=(const Vec2D& v)
{
    return *this = *this + v;
}

Vec2D Vec2D::operator-(const Vec2D& v) const
{
    return Vec2D(
                    (*this)[0] - v[0], 
                    (*this)[1] - v[1]
                );
}

Vec2D& Vec2D::operator-=(const Vec2D& v)
{
    return *this = *this - v;
}

Vec2D Vec2D::operator*(const double n) const
{
    return Vec2D(
                    (*this)[0] * n, 
                    (*this)[1] * n
                );
}


Vec2D& Vec2D::operator*=(const double n)
{
    return *this = *this * n;
}

Vec2D Vec2D::operator/(const double n) const
{
    assert(n != 0);
    return Vec2D(
                    (*this)[0] / n, 
                    (*this)[1] / n
                );
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
    return *this * *this;
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
        return *this / (*this).Norm();
}

Vec2D& Vec2D::Normalize()
{
    return *this = (*this).Direction();
}

//Vec3D
Vec3D::Vec3D(const double x, const double y, const double z)
    :
    m_xy(x,y),
    m_z(z)
{
}

Vec3D::Vec3D(const Vec2D xy, const double z)
    :
    m_xy(xy),
    m_z(z)
{
}

double& Vec3D::operator[](const int index)
{
    assert(index >= 0);
    assert(index <= 2);

    switch (index)
    {
    case 0:
        return m_xy[0];
    case 1:
        return m_xy[1];
    case 2:
        return m_z;
    default:
        return g_errD;
    }
}

const double& Vec3D::operator[](const int index) const
{
    assert(index >= 0);
    assert(index <= 2);
    switch (index)
    {
    case 0:
        return m_xy[0];
    case 1:
        return m_xy[1];
    case 2:
        return m_z;
    default:
        return g_errD;
    }
}

Vec3D Vec3D::operator+(const Vec3D& v) const
{
    return Vec3D(
        (*this)[0] + v[0],
        (*this)[1] + v[1],
        (*this)[2] + v[2]
    );
}

Vec3D& Vec3D::operator+=(const Vec3D& v)
{
    return *this = *this + v;
}

Vec3D Vec3D::operator-(const Vec3D& v) const
{
    return Vec3D(
        (*this)[0] - v[0],
        (*this)[1] - v[1],
        (*this)[2] - v[2]
    );
}

Vec3D& Vec3D::operator-=(const Vec3D& v)
{
    return *this = *this - v;
}

Vec3D Vec3D::operator*(const double n) const
{
    return Vec3D(
        (*this)[0] * n,
        (*this)[1] * n,
        (*this)[2] * n
    );
}


Vec3D& Vec3D::operator*=(const double n)
{
    return *this = *this * n;
}

Vec3D Vec3D::operator/(const double n) const
{
    assert(n != 0);
    return Vec3D(
        (*this)[0] / n,
        (*this)[1] / n,
        (*this)[2] / n
    );
}

Vec3D& Vec3D::operator/=(const double n)
{

    return *this = *this / n;
}


Vec3D Vec3D::operator-() const
{
    return *this * -1;
}

double Vec3D::operator*(const Vec3D& v) const
{
    return (*this)[0] * v[0] + (*this)[1] * v[1] + (*this)[2] * v[2];
}

Vec3D operator*(const double n, const Vec3D& v)
{
    return v * n;
}

Vec3D Vec3D::operator%(const Vec3D& v) const
{
    return Vec3D(
        (*this)[1] + v[2] - (*this)[2] + v[1],
        (*this)[2] + v[0] - (*this)[0] + v[2],
        (*this)[0] + v[1] - (*this)[1] + v[0]
    );
}

Vec3D& Vec3D::operator%=(const Vec3D& v)
{
    return *this = *this % v;
}

Vec3D operator/(const double n, const Vec3D& v)
{
    return v / n;
}

double Vec3D::NormSq() const
{
    return *this * *this;
}

double Vec3D::Norm() const
{
    return sqrt(NormSq());
}

Vec3D Vec3D::Direction() const
{
    if ((*this).NormSq() == 0)
        return *this;
    else
        return *this / (*this).Norm();
}

Vec3D& Vec3D::Normalize()
{
    return *this = (*this).Direction();
}

const Vec2D& Vec3D::Get2D() const
{
        return m_xy;
}


//integer vectors

int g_errI = std::nan("VEC_INDEX_OOB");

Vec2I::Vec2I()
    :
    m_x(0),
    m_y(0)
{
}

Vec2I::Vec2I(const int x, const int y)
    :
    m_x(x),
    m_y(y)
{
}

int& Vec2I::operator[](const int index)
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
        return g_errI;
    }
}

const int& Vec2I::operator[](const int index) const
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
        return g_errI;
    }
}

Vec2I Vec2I::operator+(const Vec2I& v) const
{
    return Vec2I(
        (*this)[0] + v[0],
        (*this)[1] + v[1]
    );
}

Vec2I& Vec2I::operator+=(const Vec2I& v)
{
    return *this = *this + v;
}

Vec2I Vec2I::operator-(const Vec2I& v) const
{
    return Vec2I(
        (*this)[0] - v[0],
        (*this)[1] - v[1]
    );
}

Vec2I& Vec2I::operator-=(const Vec2I& v)
{
    return *this = *this - v;
}

Vec2I Vec2I::operator*(const double n) const
{
    return Vec2I(
        (*this)[0] * n,
        (*this)[1] * n
    );
}


Vec2I& Vec2I::operator*=(const double n)
{
    return *this = *this * n;
}

Vec2I Vec2I::operator/(const double n) const
{
    assert(n != 0);
    return Vec2I(
        (*this)[0] / n,
        (*this)[1] / n
    );
}

Vec2I& Vec2I::operator/=(const double n)
{

    return *this = *this / n;
}


Vec2I Vec2I::operator-() const
{
    return *this * -1;
}

int Vec2I::operator*(const Vec2I& v) const
{
    return (*this)[0] * v[0] + (*this)[1] * v[1];
}

Vec2I operator*(const double n, const Vec2I& v)
{
    return v * n;
}

Vec2I operator/(const double n, const Vec2I& v)
{
    return v / n;
}

//Vec3I
Vec3I::Vec3I(const int x, const int y, const int z)
    :
    m_xy(x, y),
    m_z(z)
{
}

Vec3I::Vec3I(const Vec2I xy, const int z)
    :
    m_xy(xy),
    m_z(z)
{
}

int& Vec3I::operator[](const int index)
{
    assert(index >= 0);
    assert(index <= 2);

    switch (index)
    {
    case 0:
        return m_xy[0];
    case 1:
        return m_xy[1];
    case 2:
        return m_z;
    default:
        return g_errI;
    }
}

const int& Vec3I::operator[](const int index) const
{
    assert(index >= 0);
    assert(index <= 2);
    switch (index)
    {
    case 0:
        return m_xy[0];
    case 1:
        return m_xy[1];
    case 2:
        return m_z;
    default:
        return g_errI;
    }
}

Vec3I Vec3I::operator+(const Vec3I& v) const
{
    return Vec3I(
        (*this)[0] + v[0],
        (*this)[1] + v[1],
        (*this)[2] + v[2]
    );
}

Vec3I& Vec3I::operator+=(const Vec3I& v)
{
    return *this = *this + v;
}

Vec3I Vec3I::operator-(const Vec3I& v) const
{
    return Vec3I(
        (*this)[0] - v[0],
        (*this)[1] - v[1],
        (*this)[2] - v[2]
    );
}

Vec3I& Vec3I::operator-=(const Vec3I& v)
{
    return *this = *this - v;
}

Vec3I Vec3I::operator*(const double n) const
{
    return Vec3I(
        (*this)[0] * n,
        (*this)[1] * n,
        (*this)[2] * n
    );
}


Vec3I& Vec3I::operator*=(const double n)
{
    return *this = *this * n;
}

Vec3I Vec3I::operator/(const double n) const
{
    assert(n != 0);
    return Vec3I(
        (*this)[0] / n,
        (*this)[1] / n,
        (*this)[2] / n
    );
}

Vec3I& Vec3I::operator/=(const double n)
{

    return *this = *this / n;
}


Vec3I Vec3I::operator-() const
{
    return *this * -1;
}

int Vec3I::operator*(const Vec3I& v) const
{
    return (*this)[0] * v[0] + (*this)[1] * v[1] + (*this)[2] * v[2];
}

Vec3I operator*(const double n, const Vec3I& v)
{
    return v * n;
}

Vec3I Vec3I::operator%(const Vec3I& v) const
{
    return Vec3I(
        (*this)[1] + v[2] - (*this)[2] + v[1],
        (*this)[2] + v[0] - (*this)[0] + v[2],
        (*this)[0] + v[1] - (*this)[1] + v[0]
    );
}

Vec3I& Vec3I::operator%=(const Vec3I& v)
{
    return *this = *this % v;
}

Vec3I operator/(const double n, const Vec3I& v)
{
    return v / n;
}


const Vec2I& Vec3I::Get2D() const
{
    return m_xy;
}