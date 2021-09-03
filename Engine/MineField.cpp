#include "MineField.h"
#include "Vectors.h"
#include "Graphics.h"
#include "Grid.h"
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

void MineField::Tile::SpawnMine()
{
    assert(!m_hasMine);
    m_hasMine = true;
}

void MineField::Tile::SetState(State s)
{
    m_state = s;
}

void MineField::Tile::Draw(Graphics& gfx, const MineField& m, const Vec2I& gridPos) const
{
    switch (m_state)
    {
    case State::Hidden:
        gfx.DrawRect(RectD(m.Pos().Get2D() + gridPos * m_dim, m_dim, m_dim), Colors::Blue);
        break;
    case State::Flagged:
        gfx.DrawRect(RectD(m.Pos().Get2D() + gridPos * m_dim, m_dim, m_dim), Colors::Red);
        break;
    case State::Revealed:
        gfx.DrawRect(RectD(m.Pos().Get2D() + gridPos * m_dim, m_dim, m_dim), Colors::White);
        break;
    }
}

MineField::MineField(const Vec2I& pos, const int width, const int height, const int nMines)
    :
    Entity("Board", pos),
    m_field(width, height),
    m_border(RectD(Pos().Get2D(), width*Tile::m_dim, height*Tile::m_dim), 5, Colors::Blue)
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
}

void MineField::Draw(Graphics& gfx) const
{
    m_border.Draw(gfx);
    for (Vec2I gridPos(0,0); gridPos[1] < m_field.Height(); ++gridPos[1])
    {
        for (; gridPos[0] < m_field.Width(); ++gridPos[0])
        {
            m_field.At(gridPos).Draw(gfx, *this, gridPos);
        }
    }
}
