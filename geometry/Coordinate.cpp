#include "Coordinate.hpp"

#include "Angle.hpp"
#include "Vector.hpp"

using namespace mt;

Coordinate::Coordinate(float _x, float _y) {
    x(_x);
    y(_y);
}

float Coordinate::x() const {
    return m_x;
}

void Coordinate::x(float _x) {
    m_x = _x;
}

float Coordinate::y() const {
    return m_y;
}

void Coordinate::y(float _y) {
    m_y = _y;
}

float Coordinate::distance(const Coordinate & c) const {
    float dx = x() - c.x();
    float dy = y() - c.y();
    if (dx == 0)
        return abs(dy);
    else if (dy == 0)
        return abs(dx);
    return sqrt(pow(dx, 2) + pow(dy, 2));
}

QUADRANT Coordinate::quadrant() const {
    // first be used to determine on quadrant, then switch to pos/neg
    bool x = this->x();
    bool y = this->y();
    if (!x || !y) return NO_QUADRANT;
    // switch x y to mean pos/neg
    x = (this->x() > 0);
    y = (this->y() > 0);
    
    if (x && y) {
        return Q1;
    } else if (x) {
        return Q4;
    } else if (y) {
        return Q2;
    } else {
        return Q3;
    }
}

AXIS Coordinate::axis() const {
    if ((x() != 0) ^ (y() != 0)) {
        if (x() != 0) return X_AXIS;
        else return Y_AXIS;
    }
        
    return NO_AXIS;
}

bool Coordinate::in_quadrant(const QUADRANT _quadrant) const {
    return quadrant() == _quadrant;
}

bool Coordinate::on_axis(const AXIS _axis) const {
    return axis() == _axis;
}

Coordinate Coordinate::operator+(const Vector & _v) const {
    return Coordinate(x() + _v.dx(), y() + _v.dy());
}

Coordinate & Coordinate::operator+=(const Vector & _v) {
    x(x() + _v.dx());
    y(y() + _v.dy());
    return *this;
}

Coordinate Coordinate::operator-(const Vector & _v) const {
    return Coordinate(x() - _v.dx(), y() - _v.dy());
}

Coordinate & Coordinate::operator-=(const Vector & _v) {
    x(x() - _v.dx());
    y(y() - _v.dy());
    return *this;
}

bool Coordinate::operator==(const Coordinate & c) const {
    return (float_eq(m_x, c.x()) && float_eq(m_y, c.y()));
}

bool Coordinate::operator!=(const Coordinate & c) const {
    return !(*this == c);
}
