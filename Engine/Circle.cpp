#include "Circle.h"
#include "Vectors.h"


Circle::Circle(const Vec2D& pos, const double r)
    :
    m_pos(pos),
    m_r(r)
{
}

const Vec2D& Circle::Pos() const
{
    return m_pos;
}

double Circle::Radius() const
{
    return m_r;
}

bool Circle::IsOverlapping(const Circle& circle) const
{
    return (Pos()-circle.Pos()).NormSq() < (Radius()+circle.Radius()) * (Radius() + circle.Radius());
}

bool Circle::IsWithin(const Circle& circle) const
{
    double distSq = (Pos() - circle.Pos()).NormSq();
    double dRadius = circle.Radius() - Radius();
    return distSq < circle.Radius() * circle.Radius() && dRadius * dRadius > distSq;
}
