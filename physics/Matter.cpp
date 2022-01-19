#include "Matter.hpp"

NAMESPACES
using mt::physics::Matter;

Matter::Matter(const Coordinate & _position, const Rectangle & _space, float _mass) :
m_position(_position),
m_space(_space),
m_mass(_mass) { }

float Matter::mass() const {
    return m_mass;
}

Matter & Matter::mass(const float _mass) {
    m_mass = _mass;
    return *this;
}

Coordinate Matter::position() const {
    return m_position;
}

Matter & Matter::position(const Coordinate & _position) {
    m_position = _position;
    return *this;
}

Rectangle Matter::space() const {
    return m_space + position();
}

Matter & Matter::space(const Rectangle & _space) {
    m_space = _space;
    return *this;
}

Vector Matter::velocity() const {
    return m_velocity;
}

Matter & Matter::velocity(const Vector & _velocity) {
    m_velocity = _velocity;
    return *this;
}

Matter & Matter::add_velocity(const Vector & _velocity) {
    m_velocity += _velocity;
    return *this;
}

Matter & Matter::move(const Vector & _v) {
    m_space += _v;
    return *this;
}
