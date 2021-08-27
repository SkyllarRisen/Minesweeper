#pragma once



class Vec2D
{
public:

    Vec2D() = default;
    Vec2D(double x, double y);

    double& operator[](int index);
    const double& operator[](const int index) const;

    Vec2D operator+(const Vec2D& v) const;
    Vec2D& operator+=(const Vec2D& v) ;
    Vec2D operator-(const Vec2D& v) const;
    Vec2D& operator-=(const Vec2D& v) ;

    Vec2D operator*(const double n) const;
    friend Vec2D operator*(const double n, const Vec2D& v);
    Vec2D& operator*=(const double n) ;
    Vec2D operator/(const double n) const;
    friend Vec2D operator/(const double n, const Vec2D& v);
    Vec2D& operator/=(const double n) ;

    Vec2D operator-() const;
    double operator*(const Vec2D& v) const;

    double NormSq() const;
    double Norm() const;
    Vec2D Direction() const;
    Vec2D& Normalize();

private:
    double m_x, m_y;
};

