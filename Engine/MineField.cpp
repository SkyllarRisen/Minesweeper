#include "MineField.h"
#include "Vectors.h"
#include "Graphics.h"
#include "Grid.h"
#include "Sprite.h"
#include <cassert>
#include <random>
#include <algorithm>

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

bool MineField::Tile::IsRevealed() const
{
    return m_state == State::Revealed;
}

bool MineField::Tile::IsFlagged() const
{
    return m_state == State::Flagged;
}

int MineField::Tile::GetAdjMines() const
{
    return m_adjMines;
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
        gfx.DrawSprite(Sprites::TileHidden, Colors::Blue, m.Pos().Get2D() + gridPos * dim);
        gfx.DrawSprite(Sprites::TileFlagged, Colors::Red, m.Pos().Get2D() + gridPos * dim);
        break;
    case State::Revealed:
        gfx.DrawSprite(Sprites::Tile, Colors::Cyan, m.Pos().Get2D() + gridPos * dim);
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
            case 1:
                gfx.DrawSprite(Sprites::Tile1, Colors::Blue, m.Pos().Get2D() + gridPos * dim);
                break;
            case 2:
                gfx.DrawSprite(Sprites::Tile2, Colors::Green, m.Pos().Get2D() + gridPos * dim);
                break;
            case 3:
                gfx.DrawSprite(Sprites::Tile3, Colors::Red, m.Pos().Get2D() + gridPos * dim);
                break;
            case 4:
                gfx.DrawSprite(Sprites::Tile4, Colors::Red, m.Pos().Get2D() + gridPos * dim);
                break;
            case 5:
                gfx.DrawSprite(Sprites::Tile5, Colors::Red, m.Pos().Get2D() + gridPos * dim);
                break;
            case 6:
                gfx.DrawSprite(Sprites::Tile6, Colors::Magenta, m.Pos().Get2D() + gridPos * dim);
                break;
            case 7:
                gfx.DrawSprite(Sprites::Tile7, Colors::Magenta, m.Pos().Get2D() + gridPos * dim);
                break;
            case 8:
                gfx.DrawSprite(Sprites::Tile8, Colors::Magenta, m.Pos().Get2D() + gridPos * dim);
                break;
            default:
                break;
            }
        }
        break;
    }
}

MineField::MineField(const Vec2I& pos, const int width, const int height, const int nMines)
    :
    Entity("Board", pos),
    m_field(width, height),
    m_border(RectD(Pos().Get2D(), width*Tile::dim, height*Tile::dim), -10, Colors::Blue),
    m_gameOver(false)
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
            using std::max;
            using std::min;
            int xmin = max( 0, gridPos[0] - 1);
            int ymin = max( 0, gridPos[1] - 1);
            int xmax = min( m_field.Width() - 1, gridPos[0] + 1);
            int ymax = min( m_field.Height() - 1, gridPos[1] + 1);

            for (int j = ymin; j <= ymax; ++j)
            {
                for (int i = xmin; i <= xmax; ++i)
                {
                    if (m_field.At(Vec2I(i, j)).HasMine())
                    {
                        ++counter;
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

bool MineField::OnRevealClick(const Vec2I& screenPos)
{
    if (m_border.InnerBounds().Contains(screenPos) && !m_gameOver)
    {
        Vec2I gridPos = (screenPos - Pos().Get2D()) / Tile::dim;
        if (!(m_field.At(gridPos).IsRevealed() || m_field.At(gridPos).IsFlagged()))
        {
            m_field.At(gridPos).Reveal();
            if (m_field.At(gridPos).GetAdjMines() == 0)
            {
                RevealAdj(gridPos);
            }
            if (m_field.At(gridPos).HasMine())
            {
                m_gameOver = true;
                return false;
            }
            GameIsWon();
        }

    }
    return true;
}

void MineField::OnToggleFlagClick(const Vec2I& screenPos)
{
    if (m_border.InnerBounds().Contains(screenPos) && !m_gameOver)
    {
        Vec2I gridPos = (screenPos - Pos().Get2D()) / Tile::dim;
        if (!m_field.At(gridPos).IsRevealed())
        {
            m_field.At(gridPos).ToggleFlag();
            GameIsWon();
        }

    }
}

void MineField::RevealAdj(const Vec2I& gridPos)
{
    using std::max;
    using std::min;
    const int xmin = max(0, gridPos[0] - 1);
    const int ymin = max(0, gridPos[1] - 1);
    const int xmax = min(m_field.Width() - 1, gridPos[0] + 1);
    const int ymax = min(m_field.Height() - 1, gridPos[1] + 1);

    for (int j = ymin; j <= ymax; ++j)
    {
        for (int i = xmin; i <= xmax; ++i)
        {                
            if (!m_field.At(Vec2I(i, j)).IsRevealed())
            {
                m_field.At(Vec2I(i, j)).Reveal();
                if (m_field.At(Vec2I(i, j)).GetAdjMines() == 0)
                {
                    RevealAdj(Vec2I(i, j));
                }
            }        
        }
    }
}

bool MineField::GameIsWon()
{
    for (const Tile& t : m_field.List())
    {
        if (t.HasMine() && !t.IsFlagged() || !t.HasMine() && !t.IsRevealed())
        {
            return false;
        }
    }
    m_gameOver = true;
    return true;
}
