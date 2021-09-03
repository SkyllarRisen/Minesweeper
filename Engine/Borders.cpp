#include "Borders.h"
#include "Graphics.h"
#include <cassert>

Borders::Borders(const RectD& outerBounds, const double thickness, const Color c)
    :
    m_c(c)
{
    if (thickness < 0)
    {
        m_thickness = -thickness;
        m_innerBounds = outerBounds;
        assert(m_innerBounds.Left() - m_thickness >= 0);
        assert(m_innerBounds.Top() - m_thickness >= 0);
        assert(m_innerBounds.Right() + m_thickness < Graphics::ScreenWidth);
        assert(m_innerBounds.Bottom() + m_thickness < Graphics::ScreenHeight);
    }
    else
    {
        assert(thickness < (outerBounds.Right() - outerBounds.Left()) / 2);
        assert(thickness < (outerBounds.Bottom() - outerBounds.Top()) / 2);
        m_thickness = thickness;
        Vec2D thickVec = Vec2D(thickness, thickness);
        m_innerBounds = RectD(Vec2D(outerBounds.Left(), outerBounds.Top()) + thickVec, Vec2D(outerBounds.Right(), outerBounds.Bottom()) - thickVec);
        assert(m_innerBounds.Left() - m_thickness >= 0);
        assert(m_innerBounds.Top() - m_thickness >= 0);
        assert(m_innerBounds.Right() + m_thickness < Graphics::ScreenWidth);
        assert(m_innerBounds.Bottom() + m_thickness < Graphics::ScreenHeight);
    }
}

const RectD& Borders::InnerBounds() const
{
    return m_innerBounds;
}

const RectD Borders::OuterBounds() const
{
    Vec2D thickVec = Vec2D(m_thickness, m_thickness);
    return RectD(Vec2D(m_innerBounds.Left(), m_innerBounds.Top()) - thickVec, Vec2D(m_innerBounds.Right(), m_innerBounds.Bottom()) + thickVec);
}

void Borders::Draw(Graphics& gfx) const
{
    gfx.DrawRect(OuterBounds(), m_c);
    gfx.DrawRect(InnerBounds(), Colors::Black);
}
