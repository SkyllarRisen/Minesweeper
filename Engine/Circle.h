#pragma once
#include "Vectors.h"


class Circle
{
public:

    Circle(const Vec2D& pos, const double r);
    const Vec2D& Pos() const;
    double Radius() const;
    bool IsOverlapping(const Circle& circle) const;
    bool IsWithin(const Circle& circle) const;

private:

    double m_r;
    Vec2D m_pos;

};

