#include "Object.hpp"

#include "World.hpp"

using namespace mt;

Object::Object(World* _world, const Coordinate & _center, const float _width, const float _height, const float _z, const Vector & _velocity) {
    m_world = _world;
    width(_width);
    height(_height);
    z(_z);
    center(_center);
    velocity(_velocity);
    m_casts_shadow = (_z == 1);
    m_gravity_affected = (_z == 1);
    m_terrarin_boundaries = true;
}

void Object::update() {
    update_velocity();
    move(m_velocity);
}

void Object::update_velocity() {
    if (m_ground && m_terrarin_boundaries) {
        Angle ground_angle = m_ground->line().angle();
        m_velocity.rotate(ground_angle * -1);
        m_velocity.dy(0);
        m_velocity.rotate(ground_angle);
    } else if (!m_ground && m_gravity_affected) {
        m_velocity += GRAVITY;
    }
}

void Object::move(const Vector & _vector) {
    Vector movement = _vector;
    float movement_percentage = 0;
    Vector remaining = Vector(0, 0);
    
    shared_ptr<TerrainEdge> next_ground = m_ground;
    
    if (m_terrarin_boundaries) {
        for_each (terrain_edge, m_world->terrain().edges()) {
            if (m_ground && ((terrain_edge == m_ground) || (m_ground->vertex1() && terrain_edge.get() == m_ground->vertex1()->edge1()) || (m_ground->vertex2() && terrain_edge.get() == m_ground->vertex2()->edge2()))) continue;
            
            if (Line(m_center, m_center + _vector).intersects(terrain_edge->line() + Vector(0, height() / 2))) {
                next_ground = terrain_edge;
                movement = Line(m_center, m_center + _vector).intersection(terrain_edge->line() + Vector(0, height() / 2)) - m_center;
                movement_percentage = 0;
                if (movement.magnitude()) movement_percentage = movement.magnitude() / _vector.magnitude();
                remaining = _vector - movement;
                remaining.rotate(terrain_edge->line().angle() * -1);
                remaining.dy(0);
                remaining.rotate(terrain_edge->line().angle());
                m_velocity = remaining * (1 - movement_percentage);
            }
        }
    }
    
    if (m_ground && next_ground == m_ground) {
        if ((m_center + _vector).x() > m_ground->line().right().x()) {
            movement = m_ground->vertex2()->position() - m_center + Vector(0, height() / 2);
            movement_percentage = 0;
            if (movement.magnitude())
                movement_percentage = movement.magnitude() / _vector.magnitude();
            remaining = _vector - movement;
            if (m_ground->vertex2()->edge2()) {
                next_ground = shared_ptr<TerrainEdge>(new TerrainEdge(*m_ground->vertex2()->edge2()));
                remaining.rotate(next_ground->line().angle() * -1);
                remaining.dy(0);
                remaining.rotate(next_ground->line().angle());
            } else {
                next_ground = nullptr;
            }
            m_velocity = remaining * (1 - movement_percentage);
        } else if ((m_center + _vector).x() < m_ground->line().left().x()) {
            movement = m_ground->vertex1()->position() - m_center + Vector(0, height() / 2);
            movement_percentage = 0;
            if (movement.magnitude())
                movement_percentage = movement.magnitude() / _vector.magnitude();
            remaining = _vector - movement;
            if (m_ground->vertex1()->edge1()) {
                next_ground = shared_ptr<TerrainEdge>(new TerrainEdge(*m_ground->vertex1()->edge1()));
            } else {
                next_ground = nullptr;
            }
            m_velocity = remaining * (1 - movement_percentage);
        }
    }
    
    m_ground = next_ground;
    center(center() + movement);
    if (movement.magnitude() > 0.1 && remaining.magnitude() > 0.1)
        move(remaining); // TODO loop instead of recursive?
}

void Object::draw(const Camera & _camera) const {
    if (m_casts_shadow) draw_shadow(_camera);
}

void Object::draw_shadow(const Camera & _camera) const {
    // TODO
}

#ifdef MT_DEBUG
void Object::draw_visable_box(const Camera & _camera) const {
    if (m_width && m_height) {
        _camera.draw_polygon(Color(255, 255, 255, 64), visable_box(), 2 / _camera.zoom(), m_z);
    }
}
#endif

Coordinate Object::center() const {
    return m_center;
}

void Object::center(const Coordinate & _center) {
    m_center = _center;
}

float Object::width() const {
    return m_width;
}

void Object::width(const float _width) {
    m_width = _width;
}

float Object::height() const {
    return m_height;
}

void Object::height(const float _height) {
    m_height = _height;
}

float Object::z() const {
    return m_z;
}

void Object::z(const float _z) {
    m_z = _z;
}

Vector Object::velocity() const {
    return m_velocity;
}

void Object::velocity(const Vector & _velocity) {
    m_velocity = _velocity;
}

bool Object::terrarin_boundaries() const {
    return m_terrarin_boundaries;
}

void Object::terrarin_boundaries(bool _terrarin_boundaries) {
    m_terrarin_boundaries  = _terrarin_boundaries;
    if (!m_terrarin_boundaries) {
        m_ground = nullptr;
    }
}

bool Object::gravity_affected() const {
    return m_gravity_affected;
}

void Object::gravity_affected(bool _gravity_affected) {
    m_gravity_affected  = _gravity_affected;
}

Rectangle Object::visable_box() const {
    return Rectangle(m_width, m_height, m_center);
}
