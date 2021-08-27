#pragma once
#include "Vectors.h"
#include <string>


class Entity
{
public:

    Entity() = delete;
    Entity(std::string type, Vec2D pos = Vec2D(0, 0), Vec2D vel = Vec2D(0,0));
    Entity(std::string type, Vec3D pos, Vec3D vel = Vec3D(0,0,0));
    static unsigned int numberOfEntities;

    unsigned int ID() const;
    std::string Type() const;
    const Vec3D& Pos() const;
    const Vec3D& Vel() const;

    bool operator==(const Entity& e) const;
protected:

private:

    const std::string m_type;
    const unsigned int m_id;
    Vec3D m_pos, m_vel;
    
};

