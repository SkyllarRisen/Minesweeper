#pragma once
#include "Entity.h"
#include "Grid.h"
#include "Graphics.h"
#include "Borders.h"


class MineField : public Entity
{
public:

    MineField(const Vec2I& pos, const int width, const int height, const int nMines);

    class Tile 
    {
    public:

        Tile();

        enum class State
        { 
            Hidden, 
            Flagged,
            Revealed  
        };

        State GetState() const;
        bool HasMine() const;

        void SpawnMine();
        void SetState(State s);
        void Draw(Graphics& gfx, const MineField& m, const Vec2I& gridPos) const;
        static constexpr int m_dim = 20;

    private:

        bool m_hasMine;
        State m_state;


    };

    void Draw(Graphics& gfx) const;

private:

    Grid<Tile> m_field;
    const Borders m_border;

};

