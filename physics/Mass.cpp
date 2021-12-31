#include "Mass.hpp"

NAMESPACES
using mt::physics::Mass;

Mass::Mass(const Coordinate & _position, const float _mass) :
m_mass(_mass),
m_position(_position) { }

void Mass::move() {
    position(position() + velocity());
}

float Mass::mass() const {
    return m_mass;
}

void Mass::mass(const float _mass) {
    m_mass = _mass;
}

Coordinate Mass::position() const {
    return m_position;
}

void Mass::position(const Coordinate & _position) {
    m_position = _position;
}

Vector Mass::velocity() const {
    return m_velocity;
}

void Mass::velocity(const Vector & _velocity) {
    m_velocity = _velocity;
}

void Mass::add_velocity(const Vector & _velocity) {
    m_velocity += _velocity;
}
