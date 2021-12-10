#include "Vector.hpp"

using namespace mt;

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

void Vector::dx(float _dx) {
    m_dx = _dx;
}

float Vector::dy() const {
    return m_dy;
}

void Vector::dy(float _dy) {
    m_dy = _dy;
}

void Vector::dxdy(float _dx, float _dy) {
    dx(_dx);
    dy(_dy);
}

Coordinate Vector::origin() const {
    return m_origin;
}

void Vector::origin(const Coordinate & _origin) {
    m_origin = _origin;
}

Coordinate Vector::destination() const {
    Coordinate destination = m_origin;
    destination.x(destination.x() + m_dx);
    destination.y(destination.y() + m_dy);
    return destination;
}

void Vector::destination(Coordinate _destination) {
    dx(_destination.x() - m_origin.x());
    dy(_destination.y() - m_origin.y());
}

float Vector::magnitude() const {
    return origin().distance(destination());
}

void Vector::magnitude(float magnitude) {
    Angle a = angle();
    dx(a.cos(magnitude));
    dy(a.sin(magnitude));
}

void Vector::extend(float length) {
    magnitude(magnitude() + length);
}

Angle Vector::angle() const {
    return Angle(m_dx, m_dy);
}

void Vector::rotate_to_angle(const Angle & _angle) {
    if (angle() != _angle) {
        float _magnitude = magnitude();
        dx(_angle.cos() * _magnitude);
        dy(_angle.sin() * _magnitude);
    }
}

void Vector::rotate(const Angle & _d_angle) {
    rotate_to_angle(angle() + _d_angle);
}

void Vector::mirror_horizontal() {
    m_dx *= -1;
}

void Vector::mirror_vertical() {
    m_dy *= -1;
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
