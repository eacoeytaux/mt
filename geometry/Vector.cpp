#include "Vector.hpp"

NAMESPACES
using mt::geometry::Vector;

Vector::Vector(float _dx, float _dy, const Coordinate & _origin) {
    origin(_origin);
    dx(_dx);
    dy(_dy);
}

Vector::Vector(Angle _angle, float _magnitude, const Coordinate & _origin) {
    origin(_origin);
    
    if (_magnitude < 0) {
        _magnitude *= -1;
        _angle += PI;
    }
    
    dx(_angle.cos(_magnitude));
    dy(_angle.sin(_magnitude));
}

Vector::Vector(const Coordinate & _c1, const Coordinate & _c2) {
    origin(_c1);
    dx(_c2.x() - _c1.x());
    dy(_c2.y() - _c1.y());
}

Vector::Vector(const Coordinate & _c) {
    origin(Coordinate(0, 0));
    dx(_c.x());
    dy(_c.y());
}

float Vector::dx() const {
    return m_dx;
}

Vector & Vector::dx(float _dx) {
    m_dx = _dx;
    return *this;
}

float Vector::dy() const {
    return m_dy;
}

Vector & Vector::dy(float _dy) {
    m_dy = _dy;
    return *this;
}

Vector & Vector::dxdy(float _dx, float _dy) {
    dx(_dx);
    dy(_dy);
    return *this;
}

Coordinate Vector::origin() const {
    return m_origin;
}

Vector & Vector::origin(const Coordinate & _origin) {
    m_origin = _origin;
    return *this;
}

Coordinate Vector::destination() const {
    Coordinate destination = m_origin;
    destination.x(destination.x() + m_dx);
    destination.y(destination.y() + m_dy);
    return destination;
}

Vector & Vector::destination(Coordinate _destination) {
    dx(_destination.x() - m_origin.x());
    dy(_destination.y() - m_origin.y());
    return *this;
}

float Vector::magnitude() const {
    return origin().distance(destination());
}

Vector & Vector::magnitude(float magnitude) {
    Angle a = angle();
    dx(a.cos(magnitude));
    dy(a.sin(magnitude));
    return *this;
}

Vector & Vector::extend(float length) {
    magnitude(magnitude() + length);
    return *this;
}

Angle Vector::angle() const {
    return Angle(m_dx, m_dy);
}

Vector & Vector::rotate_to_angle(const Angle & _angle) {
    if (angle() != _angle) {
        float _magnitude = magnitude();
        dx(_angle.cos() * _magnitude);
        dy(_angle.sin() * _magnitude);
    }
    return *this;
}

Vector & Vector::rotate(const Angle & _d_angle) {
    rotate_to_angle(angle() + _d_angle);
    return *this;
}

Vector & Vector::mirror_horizontal() {
    m_dx *= -1;
    return *this;
}

Vector & Vector::mirror_vertical() {
    m_dy *= -1;
    return *this;
}

Vector Vector::operator+(const Vector & v) const {
    return Vector(m_dx + v.dx(), m_dy + v.dy(), m_origin);
}

Vector & Vector::operator+=(const Vector & v) {
    dx(m_dx + v.m_dx);
    dy(m_dy + v.m_dy);
    return *this;
}

Vector Vector::operator-(const Vector & v) const {
    return Vector(m_dx - v.dx(), m_dy - v.dy(), m_origin);
}

Vector & Vector::operator-=(const Vector & v) {
    dx(m_dx - v.m_dx);
    dy(m_dy - v.m_dy);
    return *this;
}

Vector Vector::operator*(float scale) const {
    return Vector(m_dx * scale, m_dy * scale, m_origin);
}

Vector & Vector::operator*=(float scale) {
    dx(m_dx * scale);
    dy(m_dy * scale);
    return *this;
}

Vector Vector::operator/(float scale) const {
    return Vector(m_dx / scale, m_dy / scale, m_origin);
}

Vector & Vector::operator/=(float scale) {
    dx(m_dx / scale);
    dy(m_dy / scale);
    return *this;
}

bool Vector::operator==(const Vector & v) const {
    return ((m_origin == v.m_origin) && float_eq(m_dx, v.m_dx) && float_eq(m_dy, v.m_dy));
}

bool Vector::operator!=(const Vector & v) const {
    return !(*this == v);
}
