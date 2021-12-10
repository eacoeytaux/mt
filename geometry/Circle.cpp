#include "Circle.hpp"

#include "Triangle.hpp"

using namespace mt;

Circle::Circle(float _radius, const Coordinate & _center) {
    center(_center);
    radius(_radius);
}

Coordinate Circle::center() const {
    return m_center;
}

void Circle::center(const Coordinate & _center) {
    m_center = _center;
}

float Circle::radius() const {
    return m_radius;
}

void Circle::radius(float _radius) {
    m_radius = _radius;
}

float Circle::diameter() const {
    return radius() * 2;
}

void Circle::diameter(float _diameter) {
    radius(_diameter / 2);
}

void Circle::move(const Vector & vector) {
    center(center() + vector);
}

float Circle::area() const {
    return PI * pow(radius(), 2);
}

float Circle::lower_bound_x() const {
    return center().x() - m_radius;
}

float Circle::lower_bound_y() const {
    return center().y() - m_radius;
}

float Circle::upper_bound_x() const {
    return center().x() + m_radius;
}

float Circle::upper_bound_y() const {
    return center().y() + m_radius;
}

bool Circle::contains(const Coordinate & _c) const {
    return center().distance(_c) <= m_radius;
}

float Circle::x_high(float _y) const {
    float d_y = abs(_y - center().y());
    if (d_y > radius())
        return NEG_INFINITY;
    
    float i = center().x();
    float j = center().y();
    float r = radius();
    
    return sqrt(pow(r, 2) - pow(_y - j, 2)) + i;
}

float Circle::x_low(float _y) const {
    float d_y = abs(_y - center().y());
    if (d_y > radius())
        return NEG_INFINITY;
    
    float i = center().x();
    float j = center().y();
    float r = radius();
    
    return -sqrt(pow(r, 2) - pow(_y - j, 2)) + i;
}

float Circle::y_high(float _x) const {
    float d_x = abs(_x - center().x());
    if (d_x > radius())
        return NEG_INFINITY;
    
    float i = center().x();
    float j = center().y();
    float r = radius();
    
    return sqrt(pow(r, 2) - pow(_x - i, 2)) + j;
}

float Circle::y_low(float _x) const {
    float d_x = abs(_x - center().x());
    if (d_x > radius())
        return NEG_INFINITY;
    
    float i = center().x();
    float j = center().y();
    float r = radius();
    
    return -sqrt(pow(r, 2) - pow(_x - i, 2)) + j;
}

varray<Coordinate> Circle::coordinates() const {
    varray<Coordinate> coordinates;
    Angle start_angle(PI / 2);
    Angle delta_angle = 2 * PI / CIRCLE_PRECISION;
    for_range (CIRCLE_PRECISION) {
        start_angle += delta_angle;
        Coordinate coor = center() + Vector(start_angle, radius());
        coordinates.push_back(coor);
    }
    return coordinates;
}

Path Circle::lines() const {
    Path lines;
    Angle start_angle(PI / 2);
    Angle delta_angle = 2 * PI / CIRCLE_PRECISION;
    Coordinate c1 = center() + Vector(radius(), 0);
    for_range (CIRCLE_PRECISION) {
        if (!i) continue;
        start_angle += delta_angle;
        Coordinate c2 = center() + Vector(start_angle, radius());
        Line line(c1, c2);
        lines.push_back(line);
        c1 = c2;
    }
    Line line(c1, center() + Vector(radius(), 0));
    lines.push_back(line);
    return lines;
}

Path Circle::arc(const Angle & _a1, const Angle & _a2) const {
    Angle arc = _a1 - _a2;
    Angle d_angle = arc * (CIRCLE_PRECISION_ANGLE / arc.radians());
    Vector start(_a1, radius());
    Vector end(_a2, radius());
    
//    if (d_angle < arc)
    
    varray<Line> arc_path;
    Vector v1 = start;
    Vector v2 = start;
    int point_count = (int)(d_angle.radians() / CIRCLE_PRECISION_ANGLE);
    for_range (point_count) {
        v2.rotate(d_angle * (i + 1));
        arc_path.push_back(Line(v1.destination(), v2.destination()));
        v1 = v2;
    }
    
    // confirm there is a line
    if (!arc_path.size()) return { Line(start.destination(), end.destination()) };
    
    return arc_path;
}

varray<Triangle> Circle::triangles() const {
    varray<Triangle> triangles;
    Angle start_angle(PI / 2);
    Angle delta_angle = 2 * PI / CIRCLE_PRECISION;
    Coordinate c1 = center() + Vector(radius(), 0);
    for_range (CIRCLE_PRECISION) {
        if (!i) continue;
        start_angle += delta_angle;
        Coordinate c2 = center() + Vector(start_angle, radius());
        Triangle triangle(center(), c1, c2);
        triangles.push_back(triangle);
        c1 = c2;
    }
    Triangle triangle(center(), c1, center() + Vector(radius(), 0));
    triangles.push_back(triangle);
    return triangles;
}

float Circle::convert_to_radians(float _distance) const {
    return _distance / m_radius;
}

float Circle::convert_to_distance(float _radians) const {
    return _radians * m_radius;
}

Circle Circle::operator+(const Vector & _v) const {
    return Circle(m_radius, center() + _v);
}

Circle & Circle::operator+=(const Vector & _v) {
    center(center() + _v);
    return *this;
}

Circle Circle::operator-(const Vector & _v) const {
    return Circle(m_radius, center() - _v);
}

Circle & Circle::operator-=(const Vector & _v) {
    center(center() - _v);
    return *this;
}

bool Circle::operator==(const Circle & _circle) const {
    return (float_eq(radius(), _circle.radius()) && (center() == _circle.center()));
}

bool Circle::operator!=(const Circle & _circle) const {
    return !(*this == _circle);
}
