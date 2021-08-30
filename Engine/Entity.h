#pragma once
#include "Vectors.h"
#include <string>


class Entity
{
public:

    Entity() = delete;
    Entity(const std::string type, const Vec2D& pos = Vec2D(0, 0), const Vec2D& vel = Vec2D(0,0));
    Entity(const std::string type, const Vec3D& pos, const Vec3D& vel = Vec3D(0,0,0));
    


    std::string Type() const;
    const Vec3D& Pos() const;
    const Vec3D& Vel() const;
    unsigned int ID() const;

    bool operator==(const Entity& e) const;
protected:

    void Move(const double x, const double y, const double z);
    void Move(const Vec2D& xy, const double z = 0);
    void Move(const Vec3D& xyz);
    void Pos(const double x, const double y, const double z);
    void Pos(const Vec2D& xy, const double z = 0);
    void Pos(const Vec3D& xyz);

    void ChangeVel(const double x, const double y, const double z);
    void ChangeVel(const Vec2D& xy, const double z = 0);
    void ChangeVel(const Vec3D& xyz);
    void Vel(const double x, const double y, const double z);
    void Vel(const Vec2D& xy, const double z = 0);
    void Vel(const Vec3D& xyz);

    static unsigned int numberOfEntities;

private:

    const std::string m_type;
    const unsigned int m_id;
    Vec3D m_pos, m_vel;
    
};

