#include "Mass.hpp"

NAMESPACES
using mt::physics::Mass;

Mass::Mass(const Coordinate & _position, const Vector & _velocity, const float _mass) :
m_mass(_mass),
m_position(_position)
// m_velocity(_velocity) { }
{ velocity(_velocity); }

float Mass::mass() const {
    return m_mass;
}

Mass & Mass::mass(const float _mass) {
    m_mass = _mass;
    return *this;
}

Coordinate Mass::position() const {
    return m_position;
}

Mass & Mass::position(const Coordinate & _position) {
    m_position = _position;
    return *this;
}

Vector Mass::velocity() const {
    return m_velocity;
}

Mass & Mass::velocity(const Vector & _velocity) {
    m_velocity = _velocity;
    return *this;
}

Mass & Mass::add_velocity(const Vector & _velocity) {
    m_velocity += _velocity;
    return *this;
}
