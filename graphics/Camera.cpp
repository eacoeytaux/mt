#include "Camera.hpp"

#include "SysGraphics.hpp"

NAMESPACES
using mt::graphics::Camera;

#define ROUND ceil // can be either ceil/floor

const float MIN_ZOOM = 0.64;
const float MAX_ZOOM = 2;

Camera::Camera(const Coordinate & _center, float _width, float _height, float _zoom) {
    width(_width);
    height(_height);
    center(_center);
    target(_center);
    zoom(_zoom);
    m_zoom = _zoom;
}

void Camera::render() const {
    // TODO
}

#ifdef MT_DEBUG
void Camera::debug_overlay() const {
    draw_line(CYAN, Line(center() + Vector(0, height() / 2 / zoom()), center() + Vector(0, -height() / 2 / zoom())), 1);
    draw_line(CYAN, Line(center() + Vector(width() / 2 / zoom(), 0), center() + Vector(-width() / 2 / zoom(), 0)), 1);
//    draw_shape(CYAN, Rectangle(width() * 0.5, height() * 0.5, center()), 1);
//    draw_shape(WHITE, Rectangle(width() * 0.75, height() * 0.75, center()), 1);
    draw_shape(CYAN, Circle(5 / zoom(), target()), FILLED);
    draw_shape(RED, Circle(3 / zoom(), target()), FILLED);
    draw_shape(CYAN, Circle(3 / zoom(), center()), FILLED);
}
#endif

void Camera::update(float dt) {
    m_center += Vector(m_center, m_target) * m_movement_ratio;
}

Rectangle Camera::screen() const {
    return Rectangle(center(), width(), height());
}

void Camera::draw_sprite(const Sprite & _sprite, const Coordinate & position, const float _z) const {
    for_each (gshape, _sprite.shapes()) {
        draw_shape(gshape.colors, gshape.shape + position, gshape.thickness, _z);
    }
}

#ifdef MT_DEBUG
void Camera::draw_vector(const Color & _color, const Vector & _vector, const unsigned int _thickness, const unsigned _arrow_shaft_length, const unsigned int _arrow_head_length) const {
    Vector vector = _vector * zoom();
    vector.magnitude(_arrow_shaft_length);
    draw_line(_color, Line(vector.origin(), vector.destination()), _thickness);
    draw_shape(_color, Square(_thickness, vector.destination(), _vector.angle() + (RIGHT_ANGLE / 2)));
    draw_line(_color, Line(vector.destination(), vector.destination() - Vector(vector.angle() + (PI / 4), _arrow_head_length)), _thickness);
    draw_line(_color, Line(vector.destination(), vector.destination() - Vector(vector.angle() - (PI / 4), _arrow_head_length)), _thickness);
}
#endif

void Camera::draw_line(const Color & _color, const Line & _line, const unsigned int _thickness, const float _z) const {
    Vector center_offset = Camera::center_offset();
    float zoom = Camera::zoom();
    unsigned int thickness = _thickness * zoom;
    if (_thickness) thickness = max<float>(thickness, 1);
    Coordinate c1 = (Vector(_line.c1()) * zoom).destination();
    Coordinate c2 = (Vector(_line.c2()) * zoom).destination();
    c1 += center_offset - (Vector(center()) * zoom * _z);
    c2 += center_offset - (Vector(center()) * zoom * _z);
    SysGraphics::draw_line(_color, Line(c1, c2), thickness);
}
    
void Camera::draw_lines(const Colors & _colors, const varray<Line> & _lines, const unsigned int _thickness, const float _z) const {
    for_range (_lines.size()) draw_line(_colors[i], _lines[i], _thickness);
}

void Camera::draw_shape(const Color & _color, const Shape & _shape, const unsigned int _thickness, float _z) const {
    Colors colors;
    for_range (_shape.coordinates().size()) colors.push_back(_color);
    draw_shape(colors, _shape, _thickness, _z);
}
    
void Camera::draw_shape(const Colors & _colors, const Shape & _shape, const unsigned int _thickness, float _z) const {
    Vector center_offset = Camera::center_offset();
    float zoom = Camera::zoom();
    
    unsigned int thickness = _thickness * zoom;
    if (_thickness) thickness = max<int>(thickness, 1);
    
    varray<Coordinate> coordinates = { };
    for_each (coordinate, _shape.coordinates()) {
        Coordinate new_coor = coordinate;
        // this adjusts scale according to zoom
        if (_z) new_coor = (Vector(coordinate) * zoom * _z).destination();
        
        Vector position_offset = Vector(center()) * zoom * _z;
        
        new_coor += center_offset;
        new_coor -= position_offset;
        
        coordinates.push_back(new_coor);
    }
    
    SysGraphics::draw_polygon(_colors, Polygon(coordinates), thickness);
}

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

void Camera::zoom(const float _zoom) {
    Assert::soft(_zoom > 0, "zoom (%f) cannot be <= 0", _zoom);
    float new_zoom = max(min(_zoom, MAX_ZOOM), MIN_ZOOM);
    float zoom_delta = new_zoom - m_zoom;
    m_zoom += zoom_delta;
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

Vector Camera::center_offset() const {
    return Vector(width() / 2, height() / 2);
}
