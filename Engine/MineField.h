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
        bool IsRevealed();
        bool IsFlagged();

        void Reveal();
        void ToggleFlag();
        void SpawnMine();
        void SetAdjMines(const int n);
        void Draw(Graphics& gfx, const MineField& m, const Vec2I& gridPos) const;
        static constexpr int dim = 30;

    private:

        bool m_hasMine;
        State m_state;
        int m_adjMines;


    };
    void OnRevealClick(const Vec2I& screenPos);
    void OnToggleFlagClick(const Vec2I& screenPos);
    void Draw(Graphics& gfx) const;

private:

    Grid<Tile> m_field;
    const Borders m_border;

};

