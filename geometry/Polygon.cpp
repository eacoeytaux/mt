#include "Polygon.hpp"

#include "Vector.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"

using namespace mt;

Polygon::Polygon(const varray<Coordinate> & _coordinates) :
m_coordinates(_coordinates) {
    m_coordinates = _coordinates;
    for_each (coordinate, _coordinates) {
        m_lower_bound_x = min<float>(lower_bound_x(), coordinate.x());
        m_lower_bound_y = min<float>(lower_bound_y(), coordinate.y());
        m_upper_bound_x = max<float>(lower_bound_x(), coordinate.x());
        m_upper_bound_x = max<float>(lower_bound_y(), coordinate.y());
    }
}

Polygon::Polygon(const varray<Vector> & _coordinate_offsets, const Coordinate & _center, Angle _rotation) {
    varray<Coordinate> coordinates;
    for_each (coordinate_offset, _coordinate_offsets) {
        coordinate_offset.rotate(_rotation);
        Coordinate coordinate = _center + coordinate_offset;
        coordinates.push_back(coordinate);
    }
    *this = Polygon(coordinates);
}

Polygon::Polygon(const Circle & _circle) {
    *this = Polygon(CIRCLE_PRECISION, _circle.radius(), _circle.center());
}

Polygon::Polygon(const Triangle & _triangle) {
    *this = Polygon(varray<Coordinate>({ _triangle.c1(), _triangle.c2(), _triangle.c3() }));
}

Polygon::Polygon(const Rectangle & _rectangle) {
    *this = Polygon(varray<Coordinate>({ _rectangle.top_right(), _rectangle.bottom_right(), _rectangle.bottom_left(), _rectangle.top_left() }));
}

Polygon::Polygon(int _side_count, float _radius, const Coordinate & _center, Angle _rotation) {
    varray<Vector> coordinate_offsets;
    Angle start_angle(PI / 2);
    start_angle += _rotation;
    Angle delta_angle = 2 * PI / _side_count;
    for_range (_side_count) {
        coordinate_offsets.push_back(Vector(start_angle, _radius));
        start_angle += delta_angle;
    }
    *this = Polygon(coordinate_offsets, _center);
}

void Polygon::rotate_around_origin(const Angle & _angle, const Coordinate & _origin) {
    varray<Coordinate> new_coordinates;
    for_each (coordinate, coordinates()) {
        Vector coor_pos = Vector(coordinate);
        coor_pos -= _origin;
        coor_pos.rotate(_angle);
        coor_pos += _origin;
        new_coordinates.push_back(coor_pos.destination());
    }
    *this = Polygon(new_coordinates);
}

float Polygon::lower_bound_x() const {
    return m_lower_bound_x;
}

float Polygon::lower_bound_y() const {
    return m_lower_bound_y;
}

float Polygon::upper_bound_x() const {
    return m_upper_bound_x;
}

float Polygon::upper_bound_y() const {
    return m_upper_bound_y;
}

varray<Coordinate> Polygon::coordinates() const {
    return m_coordinates;
}

Path Polygon::lines() const {
    Path lines;
    for_range (coordinates().size()) {
        if (!i) continue;
        Line line(coordinates()[i - 1], coordinates()[i]);
        lines.push_back(line);
    }
    Line line(coordinates()[coordinates().size() - 1], coordinates()[0]);
    lines.push_back(line);
    return lines;
}

varray<Triangle> Polygon::triangles() const {
    return varray<Triangle>(); // TODO
}

Polygon Polygon::operator+(const Vector & _v) const {
    varray<Coordinate> moved_coordinates;
    for_each (coordinate, coordinates()) {
        moved_coordinates.push_back(coordinate + _v);
    }
    return Polygon(moved_coordinates);
}

Polygon & Polygon::operator+=(const Vector & _v) {
    *this = *this + _v;
    return *this;
}

Polygon Polygon::operator-(const Vector & _v) const {
    return *this + (_v * -1);
}

Polygon & Polygon::operator-=(const Vector & _v) {
    *this += (_v * -1);
    return *this;
}

bool Polygon::operator==(const Polygon & _polygon) const {
    if (coordinates().size() != _polygon.coordinates().size()) return false;
    for_range (coordinates().size()) if (coordinates()[i] != _polygon.coordinates()[i]) return false;
    return true;
}

bool Polygon::operator!=(const Polygon & _polygon) const {
    return !(*this == _polygon);
}