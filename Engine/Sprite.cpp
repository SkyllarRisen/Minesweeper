#include "Sprite.h"
#include "Colors.h"
#include <cassert>

Sprite::Sprite(const std::vector<unsigned char>& v, Color c)
{
    assert(v.size() == Sprite::dim * Sprite::dim);
    const unsigned char r = c.GetR();
    const unsigned char g = c.GetG();
    const unsigned char b = c.GetB();
    for (const int& m : v)
    {
        assert(m >= 0);
        assert(m <= 255);
        double cMod = m / 255.0;
        m_pixels.push_back(Color((unsigned char) (r * cMod), (unsigned char) (g * cMod), (unsigned char) (b * cMod)));
    }
}

const std::vector<Color>& Sprite::GetSprite() const
{
    return m_pixels;
}
