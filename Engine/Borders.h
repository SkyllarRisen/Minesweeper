#pragma once
#include "Rect.h"
#include "Colors.h"

class Borders
{
public:
    Borders(const RectD& outerBounds, const double thickness, const Color c);
    const RectD& InnerBounds() const;
    const RectD OuterBounds() const;
    void Draw() const;
private:
    RectD m_innerBounds;
    double m_thickness;
    Color m_c;
};

