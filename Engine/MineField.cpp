#include "MineField.h"
#include "Vectors.h"
#include "Graphics.h"
#include "Grid.h"
#include "Sprite.h"
#include <cassert>
#include <random>

MineField::Tile::Tile()
    :
    m_hasMine(false),
    m_state(State::Hidden)
{
}

MineField::Tile::State MineField::Tile::GetState() const
{
    return m_state;
}

bool MineField::Tile::HasMine() const
{
    return m_hasMine;
}

bool MineField::Tile::IsRevealed()
{
    return m_state == State::Revealed;
}

bool MineField::Tile::IsFlagged()
{
    return m_state == State::Flagged;
}

void MineField::Tile::Reveal()
{
    assert(m_state == State::Hidden);
    m_state = State::Revealed;
}

void MineField::Tile::ToggleFlag()
{
    assert(!IsRevealed());
    if (!IsFlagged())
    {
        m_state = State::Flagged;
    }
    else
    {
        m_state = State::Hidden;
    }
}

void MineField::Tile::SpawnMine()
{
    assert(!m_hasMine);
    m_hasMine = true;
}

void MineField::Tile::SetAdjMines(const int n)
{
    m_adjMines = n;
}



void MineField::Tile::Draw(Graphics& gfx, const MineField& m, const Vec2I& gridPos) const
{
    switch (m_state)
    {
    case State::Hidden:
        gfx.DrawSprite(Sprites::TileHidden, Colors::Blue, m.Pos().Get2D() + gridPos * dim);
        break;
    case State::Flagged:
        gfx.DrawRect(RectD(m.Pos().Get2D() + gridPos * dim, dim, dim), Colors::Red);
        break;
    case State::Revealed:
        gfx.DrawSprite(Sprites::Tile, Colors::Blue, m.Pos().Get2D() + gridPos * dim);
        if (HasMine())
        {
            gfx.DrawRect(RectD(m.Pos().Get2D() + Vec2I(5, 5) + gridPos * dim, dim-10, dim-10), Colors::Red);
        }
        else
        {
            assert(m_adjMines >= 0);
            assert(m_adjMines <= 8);
            switch (m_adjMines)
            {

            }
        }
        break;
    }
}

MineField::MineField(const Vec2I& pos, const int width, const int height, const int nMines)
    :
    Entity("Board", pos),
    m_field(width, height),
    m_border(RectD(Pos().Get2D(), width*Tile::dim, height*Tile::dim), -10, Colors::Blue)
{
    assert(width > 0);
    assert(height > 0);
    assert(nMines > 0);
    assert(nMines < width* height);
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> xDist(0, width - 1);
    std::uniform_int_distribution<int> yDist(0, height - 1);
    for (int i = 0; i < nMines; ++i)
    {
        Vec2I spawnPos;

        do
        {
            spawnPos = Vec2I(xDist(gen), yDist(gen));
        } while (m_field.At(spawnPos).HasMine());

        m_field.At(spawnPos).SpawnMine();
    }
    for (Vec2I gridPos(0, 0); gridPos[1] < m_field.Height(); ++gridPos[1])
    {
        for (gridPos[0] = 0; gridPos[0] < m_field.Width(); ++gridPos[0])
        {
            int counter = 0;
            for (int j = gridPos[1] - 1; j <= gridPos[1] + 1; ++j)
            {
                if (j >= 0 && j < m_field.Height())
                {
                    for (int i = gridPos[0] - 1; i <= gridPos[0] + 1; ++i)
                    {
                        if (i >= 0 && i < m_field.Width())
                        {
                            if (m_field.At(Vec2I(i, j)).HasMine())
                            {
                                ++counter;
                            }
                        }
                    }
                }
            }
            m_field.At(gridPos).SetAdjMines(counter);
        }
    }
}

void MineField::Draw(Graphics& gfx) const
{
    m_border.Draw(gfx);
    for (Vec2I gridPos(0,0); gridPos[1] < m_field.Height(); ++gridPos[1])
    {
        for (gridPos[0] = 0; gridPos[0] < m_field.Width(); ++gridPos[0])
        {
            m_field.At(gridPos).Draw(gfx, *this, gridPos);
        }
    }
}

void MineField::OnRevealClick(const Vec2I& screenPos)
{
    if (m_border.InnerBounds().Contains(screenPos))
    {
        Vec2I gridPos = (screenPos - Pos().Get2D()) / Tile::dim;
        if (!(m_field.At(gridPos).IsRevealed() || m_field.At(gridPos).IsFlagged()))
        {
            m_field.At(gridPos).Reveal();
        }
    }

}

void MineField::OnToggleFlagClick(const Vec2I& screenPos)
{
    if (m_border.InnerBounds().Contains(screenPos))
    {
        Vec2I gridPos = (screenPos - Pos().Get2D()) / Tile::dim;
        if (!m_field.At(gridPos).IsRevealed())
        {
            m_field.At(gridPos).ToggleFlag();
        }
    }
}
