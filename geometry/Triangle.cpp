#include "Triangle.hpp"

using namespace mt;

Triangle::Triangle(const Coordinate & _c1, const Coordinate & _c2, const Coordinate & _c3) {
    m_c1 = _c1;
    m_c2 = _c2;
    m_c3 = _c3;
}

Triangle::Triangle(const Vector & _offset1, const Vector & _offset2, const Vector & _offset3, const Coordinate & _origin) {
    *this = Triangle(_origin + _offset1, _origin + _offset2, _origin + _offset3);
}

Coordinate Triangle::c1() const {
    return m_c1;
}

Coordinate Triangle::c2() const {
    return m_c2;
}

Coordinate Triangle::c3() const {
    return m_c3;
}

Line Triangle::line1() const {
    return Line(c1(), c2());
}

Line Triangle::line2() const {
    return Line(c2(), c3());
}

Line Triangle::line3() const {
    return Line(c3(), c1());
}

float Triangle::area() const {
    // Heron's formula
    float a = line1().length();
    float b = line2().length();
    float c = line3().length();
    float s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

varray<Coordinate> Triangle::coordinates() const {
    return varray<Coordinate>({ c1(), c2(), c3() });
}

Path Triangle::lines() const {
    return Path({ line1(), line2(), line3() });
}

varray<Triangle> Triangle::triangles() const {
    return { *this };
}

Triangle Triangle::operator+(const Vector & _v) const {
    return Triangle(c1() + _v, c2() + _v, c3() + _v);
}

Triangle & Triangle::operator+=(const Vector & _v) {
    *this = Triangle(c1() + _v, c2() + _v, c3() + _v);
    return *this;
}

Triangle Triangle::operator-(const Vector & _v) const {
    return *this + (_v * -1);
}

Triangle & Triangle::operator-=(const Vector & _v) {
    *this += (_v * -1);
    return *this;
}

bool Triangle::operator==(const Triangle & _triangle) const {
    return ((c1() == _triangle.c1()) && (c2() == _triangle.c2()) && (c3() == _triangle.c3()));
}

bool Triangle::operator!=(const Triangle & _triangle) const {
    return !(*this == _triangle);
}
