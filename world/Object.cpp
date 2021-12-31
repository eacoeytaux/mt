#include "Object.hpp"

#include "World.hpp"

NAMESPACES
using mt::exists::Object;

Object::Object(World* _world, const Coordinate & _position, const float _width, const float _height, const float _z, const Vector & _velocity) {
    m_world = _world;
    width(_width);
    height(_height);
    z(_z);
    position(_position);
    velocity(_velocity);
    m_casts_shadow = (_z == 1);
    m_gravity_affected = (_z == 1);
    m_terrarin_boundaries = true;
}

void Object::update() {
    move();
}

void Object::update_velocity() {
    Vector velocity = Mass::velocity();
    if (m_ground && m_terrarin_boundaries) {
        Angle ground_angle = m_ground->line().angle();
        velocity.rotate(ground_angle * -1);
        velocity.dy(0);
        velocity.rotate(ground_angle);
    } else if (!m_ground && m_gravity_affected) {
        velocity += GRAVITY;
    }
    Mass::velocity(velocity);
}

void Object::move() {
    update_velocity();
    Mass::move();
    
    Vector _vector(0, 0); // TODO!!!
    Coordinate center = position();
    
    if (!_vector.magnitude()) return;
    
    Vector movement = _vector;
    float movement_percentage = 0;
    Vector remaining = Vector(0, 0);
    
    shared_ptr<TerrainEdge> next_ground = m_ground;
    
    if (m_terrarin_boundaries) {
        for_each (terrain_edge, m_world->terrain().edges()) {
            if (m_ground && ((terrain_edge == m_ground) || (m_ground->vertex1() && terrain_edge.get() == m_ground->vertex1()->edge1()) || (m_ground->vertex2() && terrain_edge.get() == m_ground->vertex2()->edge2()))) continue;
            
            if (Line(center, center + _vector).intersects(terrain_edge->line() + Vector(0, height() / 2))) {
                next_ground = terrain_edge;
                movement = Line(center, center + _vector).intersection(terrain_edge->line() + Vector(0, height() / 2)) - center;
                movement_percentage = 0;
                if (movement.magnitude()) movement_percentage = movement.magnitude() / _vector.magnitude();
                remaining = _vector - movement;
                remaining.rotate(terrain_edge->line().angle() * -1);
                remaining.dy(0);
                remaining.rotate(terrain_edge->line().angle());
                velocity(remaining * (1 - movement_percentage));
            }
        }
    }
    
    if (m_ground && next_ground == m_ground) {
        if ((center + _vector).x() > m_ground->line().right().x()) {
            movement = m_ground->vertex2()->position() - center + Vector(0, height() / 2);
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
            velocity(remaining * (1 - movement_percentage));
        } else if ((center + _vector).x() < m_ground->line().left().x()) {
            movement = m_ground->vertex1()->position() - center + Vector(0, height() / 2);
            movement_percentage = 0;
            if (movement.magnitude())
                movement_percentage = movement.magnitude() / _vector.magnitude();
            remaining = _vector - movement;
            if (m_ground->vertex1()->edge1()) {
                next_ground = shared_ptr<TerrainEdge>(new TerrainEdge(*m_ground->vertex1()->edge1()));
            } else {
                next_ground = nullptr;
            }
            velocity(remaining * (1 - movement_percentage));
        }
    }
    
    m_ground = next_ground;
    position(position() + movement);
    if (movement.magnitude() > 0.1 && remaining.magnitude() > 0.1)
        move(); // TODO loop instead of recursive?
}

void Object::draw(const Camera * _camera) const {
    if (m_casts_shadow) draw_shadow(_camera);
}

void Object::draw_shadow(const Camera * _camera) const {
    // TODO
}

#ifdef MT_DEBUG
void Object::draw_visable_box(const Camera * _camera) const {
    if (m_width && m_height) {
        _camera->draw_polygon(Color(255, 255, 255, 64), visable_box(), 2 / _camera->zoom(), m_z);
    }
}
#endif

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
    return Rectangle(width(), height(), position());
}
