#include "Camera.hpp"

#include "SysGraphics.hpp"

NAMESPACES
using mt::graphics::Camera;

const float MIN_ZOOM = 0.25;
const float MAX_ZOOM = 4;

Camera::Camera(const Coordinate & _center, float _width, float _height, float _zoom) {
    width(_width);
    height(_height);
    center(_center);
    target(_center);
    zoom(_zoom);
    m_zoom = _zoom;
}

void Camera::update() {
    float zoom_delta = (m_zoom_target - m_zoom) * m_movement_ratio;
    m_zoom += zoom_delta;
    m_center += Vector(m_center, (Vector(m_target) * m_zoom).destination()) * m_movement_ratio;
}

Rectangle Camera::screen() const {
    return Rectangle(center(), width(), height());
}

#ifdef MT_DEBUG
void Camera::draw_vector(const Color & _color, const Vector & _vector, const unsigned int _thickness, const unsigned _arrow_shaft_length, const unsigned int _arrow_head_length) const {
    Vector vector = _vector;
    vector *= m_zoom;
    vector.origin(Coordinate(vector.origin().x() * m_zoom, vector.origin().y() * m_zoom));
    vector.origin(vector.origin() + Vector(width() / 2, height() / 2) - Vector(m_center));
    SysGraphics::draw_vector(_color, vector, _thickness, _arrow_shaft_length, _arrow_head_length);
}
#endif

void Camera::draw_line(const Color & _color, const Line & _line, const unsigned int _thickness, const float _z) const {
    unsigned int thickness = _thickness * m_zoom;
    if (_thickness) thickness = max<int>(thickness, 1);
    Coordinate c1 = (Vector(_line.c1()) * m_zoom).destination();
    Coordinate c2 = (Vector(_line.c2()) * m_zoom).destination();
    c1 += Vector(width() / 2, height() / 2) - (Vector(m_center) * _z);
    c2 += Vector(width() / 2, height() / 2) - (Vector(m_center) * _z);
    SysGraphics::draw_line(_color, Line(c1, c2), thickness);
}

void Camera::draw_lines(const Color & _color, const varray<Line> & _path, const unsigned int _thickness, const float _z) const {
    Colors colors;
    for_range (_path.size()) colors.push_back(_color);
    draw_lines(colors, _path, _thickness);
}
    
void Camera::draw_lines(const Colors & _colors, const varray<Line> & _path, const unsigned int _thickness, const float _z) const {
    for_range (_path.size()) draw_line(_colors[i], _path[i], _thickness);
}

void Camera::draw_triangle(const Color & _color, const Triangle & _triangle, const unsigned int _thickness, float _z) const {
    draw_triangle(varray<Color>(3, _color), _triangle, _thickness);
}

void Camera::draw_triangle(const Colors & _colors, const Triangle & _triangle, const unsigned int _thickness, float _z) const {
    // TODO
    SysGraphics::draw_triangle(_colors, _triangle, _thickness);
}

void Camera::draw_rectangle(const Color & _color, const Rectangle & _rectangle, const unsigned int _thickness, float _z) const {
    draw_rectangle(varray<Color>(4, _color), _rectangle, _thickness, _z);
}

void Camera::draw_rectangle(const Colors & _colors, const Rectangle & _rectangle, const unsigned int _thickness, float _z) const {
    unsigned int thickness = _thickness * m_zoom;
    if (_thickness) thickness = max<int>(thickness, 1);
    Rectangle rectangle = _rectangle;
    rectangle.center(Coordinate(rectangle.center().x() * m_zoom, rectangle.center().y() * m_zoom));
    rectangle.width(rectangle.width() * m_zoom);
    rectangle.height(rectangle.height() * m_zoom);
    rectangle.move(Vector(width() / 2, height() / 2) - (Vector(m_center) * _z));
    SysGraphics::draw_rectangle(_colors, rectangle, thickness);
}

void Camera::draw_square(const Color & _color, const Square & _square, const unsigned int _thickness, float _z) const {
    draw_rectangle(_color, _square, _thickness, _z);
}

void Camera::draw_square(const Colors & _colors, const Square & _square, const unsigned int _thickness, float _z) const {
    draw_rectangle(_colors, _square, _thickness, _z);
}

void Camera::draw_polygon(const Color & _color, const Polygon & _polygon, const unsigned int _thickness, float _z) const {
    Colors colors;
    for_range (_polygon.coordinates().size()) colors.push_back(_color);
    draw_polygon(colors, _polygon, _thickness);
}
    
void Camera::draw_polygon(const Colors & _colors, const Polygon & _polygon, const unsigned int _thickness, float _z) const {
    unsigned int thickness = _thickness * m_zoom;
    if (_thickness) thickness = max<int>(thickness, 1);
    varray<Coordinate> coordinates = { };
    for_each (coordinate, _polygon.coordinates()) {
        Coordinate new_coor = ((Vector(coordinate) * m_zoom) + Vector(width() / 2, height() / 2) - (Vector(m_center) * _z)).destination();
        coordinates.push_back(new_coor);
    }
    SysGraphics::draw_polygon(_colors, Polygon(coordinates), thickness);
}

void Camera::draw_circle(const Color & _color, const Circle & _circle, const unsigned int _thickness, const float _z) const {
    unsigned int thickness = _thickness * m_zoom;
    if (_thickness) thickness = max<int>(thickness, 1);
    Circle circle = _circle;
    if (m_zoom != 1) {
        circle.center(Coordinate(circle.center().x() * m_zoom, circle.center().y() * m_zoom));
        circle.radius(circle.radius() * m_zoom);
    }
    circle.move(Vector(width() / 2, height() / 2) - (Vector(m_center) * _z));
    SysGraphics::draw_circle(_color, circle, thickness);
}
    
void Camera::draw_circle(const Colors & _colors, const Circle & _circle, const unsigned int _thickness, const float _z) const {
    unsigned int thickness = _thickness * m_zoom;
    if (_thickness) thickness = max<int>(thickness, 1);
    Circle circle = _circle;
    if (m_zoom != 1) {
        circle.center(Coordinate(circle.center().x() * m_zoom, circle.center().y() * m_zoom));
        circle.radius(circle.radius() * m_zoom);
    }
    circle.move(Vector(width() / 2, height() / 2) - (Vector(m_center) * _z));
    SysGraphics::draw_circle(_colors, circle, thickness);
}

//void Camera::draw_shape(const Color & _color, const Shape & _shape, const unsigned int _thickness, float _z) const {
//    Colors colors;
//    for_range (_shape.coordinates().size()) colors.push_back(_color);
//    draw_shape(colors, _shape, _thickness);
//}

//void Camera::draw_shape(const Colors & _color, const Shape & _shape, const unsigned int _thickness, float _z) const {
//    SysGraphics.draw_shape(_colors, _shape, _thickness);
//}

float Camera::width() const {
    return m_width;
}

void Camera::width(float _width) {
    m_width = _width;
}

float Camera::height() const {
    return m_height;
}

void Camera::height(float _height) {
    m_height = _height;
}

float Camera::zoom() const {
    return m_zoom;
}

void Camera::zoom(float _zoom) {
    Assert::debug(_zoom > 0, "zoom (%f) cannot be <= 0", _zoom);
    m_zoom_target = max(min(_zoom, MAX_ZOOM), MIN_ZOOM);
}

Coordinate Camera::center() const {
    return m_center;
}

void Camera::center(const Coordinate & _center) {
    m_center = _center;
}

Coordinate Camera::target() const {
    return m_target;
}

void Camera::target(const Coordinate & _target) {
    m_target = _target;
}
