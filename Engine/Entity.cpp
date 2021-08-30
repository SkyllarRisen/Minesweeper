#include "Entity.h"
#include "Vectors.h"



unsigned int Entity::numberOfEntities = 0u;


Entity::Entity(const std::string type, const Vec2D& pos, const Vec2D& vel)
    :
    m_type(type),
    m_id(numberOfEntities++),
    m_pos(pos),
    m_vel(vel)
{
}

Entity::Entity(const std::string type, const Vec3D& pos, const Vec3D& vel)
    :
    m_type(type),
    m_id(numberOfEntities++),
    m_pos(pos),
    m_vel(vel)
{
}

std::string Entity::Type() const
{
    return m_type;
}

unsigned int Entity::ID() const
{
    return m_id;
}

const Vec3D& Entity::Pos() const
{

    return m_pos;   
}

const Vec3D& Entity::Vel() const
{
    return m_vel;
}



void Entity::Move(const double x, const double y, const double z)
{
    Move(Vec3D(x, y, z));
}

void Entity::Move(const Vec2D& xy, const double z)
{
    Move(Vec3D(xy, z));
}

void Entity::Move(const Vec3D& xyz)
{
    m_pos += xyz;
}

void Entity::Pos(const double x, const double y, const double z)
{
    Pos(Vec3D(x, y, z));
}

void Entity::Pos(const Vec2D& xy, const double z)
{
    Pos(Vec3D(xy, z));
}

void Entity::Pos(const Vec3D& xyz)
{
    m_pos = xyz;
}

void Entity::ChangeVel(const double x, const double y, const double z)
{
    ChangeVel(Vec3D(x, y, z));
}

void Entity::ChangeVel(const Vec2D& xy, const double z)
{
    ChangeVel(Vec3D(xy, z));
}

void Entity::ChangeVel(const Vec3D& xyz)
{
    m_vel += xyz;
}

void Entity::Vel(const double x, const double y, const double z)
{
    Vel(Vec3D(x, y, z));
}

void Entity::Vel(const Vec2D& xy, const double z)
{
    Vel(Vec3D(xy, z));
}

void Entity::Vel(const Vec3D& xyz)
{
    m_vel = xyz;
}

bool Entity::operator==(const Entity& e) const
{
    return (*this).ID() == e.ID();
}




