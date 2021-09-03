#pragma once
#include "Rect.h"
#include "Colors.h"
#include "Graphics.h"

class Borders
{
public:
    Borders(const RectD& outerBounds, const double thickness, const Color c);
    const RectD& InnerBounds() const;
    const RectD OuterBounds() const;
    void Draw(Graphics& gfx) const;
private:
    RectD m_innerBounds;
    double m_thickness;
    Color m_c;
};

