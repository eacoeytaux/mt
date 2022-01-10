#include "Object.hpp"

#include "World.hpp"
#include "Terrain.hpp"

NAMESPACES
using mt::exst::Object;

const float SHADOW_ALPHA = 64;
const float SHADOW_WIDTH_SCALE = 0.36; // (0, 1]
const float SHADOW_THICKNESS = 4;

Object::Object(World* _world, const Coordinate & _position, const float _width, const float _height, const float _z, const Vector & _velocity) {
    m_world = _world;
    layer_position(1);
    width(_width);
    height(_height);
    z(_z);
    position(_position);
    velocity(_velocity);
    m_casts_shadow = true;
    m_terrarin_boundaries = true;
}

void Object::update(float dt) {
    update_move(dt);
}

void Object::update_move(float dt) {
    move(dt);
}

void Object::adjust_velocity(float dt) {
    Vector velocity = Mass::velocity();
    
    if (m_ground && m_terrarin_boundaries) {
        Angle ground_angle = m_ground->line().angle();
        velocity.rotate(ground_angle * -1);
        velocity.dy(0);
        velocity.rotate(ground_angle);
    } else if (!m_ground && m_gravity_ratio) {
        velocity += (GRAVITY * m_gravity_ratio);
    }
    
    velocity *= resistance();
    
    Mass::velocity(velocity);
}

void Object::move(float dt) {
    adjust_velocity(dt);
    
    Coordinate center = position();
    Vector current_velocity = velocity();
    Vector velocity = current_velocity * dt;
    Vector movement = Vector(center, center + velocity);
    float movement_percentage = 0;
    Vector remaining = Vector(0, 0);
    
    shared_ptr<TerrainEdge> next_ground = m_ground;
    
    if (m_terrarin_boundaries) {
        if (m_ground) {
            if ((velocity.dx() > 0) && float_eq(center.x(), m_ground->vertex2()->position().x())) {
                m_ground = m_ground->vertex2()->edge2();
            }
        }
        
        for_each (terrain_edge, m_world->terrain()->edges()) {
            // skip if terrain_edge is current ground
            if (terrain_edge == m_ground) continue;
            
            Line movement_line = Line(center, center + velocity);
            if (movement_line.intersects(terrain_edge->line() + Vector(0, height() / 2))) {
                next_ground = terrain_edge;
                Coordinate intersection = movement_line.intersection(terrain_edge->line() + Vector(0, height() / 2));
                movement = Vector(center, intersection);
                movement_percentage = 0;
                if (movement.magnitude()) movement_percentage = movement.magnitude() / velocity.magnitude();
                remaining = velocity - movement;
                remaining.rotate(terrain_edge->line().angle() * -1);
                remaining.dy(0);
                remaining.rotate(terrain_edge->line().angle());
                Object::velocity(remaining * (1 - movement_percentage));
            }
        }
    }
    
    if (m_ground && next_ground == m_ground) {
        if ((velocity.dx() > 0) && (center + velocity).x() > m_ground->line().right().x()) {
            movement = m_ground->vertex2()->position() - center + Vector(0, height() / 2);
            movement_percentage = 0;
            if (movement.magnitude())
                movement_percentage = movement.magnitude() / velocity.magnitude();
            remaining = velocity - movement;
            if (m_ground->vertex2()->edge2()) {
                next_ground = m_ground->vertex2()->edge2();
//                remaining.rotate(next_ground->line().angle() * -1);
//                remaining.dy(0);
//                remaining.rotate(next_ground->line().angle());
            } else {
                next_ground = nullptr;
            }
            Object::velocity(remaining * (1 - movement_percentage));
        } else if ((velocity.dx() < 0) && (center + velocity).x() < m_ground->line().left().x()) {
            movement = m_ground->vertex1()->position() - center + Vector(0, height() / 2);
            movement_percentage = 0;
            if (movement.magnitude())
                movement_percentage = movement.magnitude() / velocity.magnitude();
            remaining = velocity - movement;
            if (m_ground->vertex1()->edge1()) {
                next_ground = m_ground->vertex1()->edge1();
//                remaining.rotate(next_ground->line().angle() * -1);
//                remaining.dy(0);
//                remaining.rotate(next_ground->line().angle());
            } else {
                next_ground = nullptr;
            }
            Object::velocity(remaining * (1 - movement_percentage));
        }
    }
    
    m_ground = next_ground;
    position(position() + movement);
    
    if (float_gt(movement_percentage, 0)) {
        move(dt * movement_percentage);
    }
}

float Object::resistance() const {
    if (m_terrarin_boundaries && m_ground) {
        return m_ground->resistance();
    }
    return AIR_RESISTANCE;
}

void Object::draw(const Camera * _camera) const {
    if (m_casts_shadow) draw_shadow(_camera);
}

void Object::draw_shadow(const Camera * _camera) const {
    if (m_ground) {
        Coordinate base = position() - Vector(0, height() / 2);
        Line shadow = Line(base - Vector(m_ground->line().angle(), (width() / 2) * SHADOW_WIDTH_SCALE), base + Vector(m_ground->line().angle(), (width() / 2) * SHADOW_WIDTH_SCALE));
//        _camera->draw_line(Color(BLACK, SHADOW_ALPHA), shadow, SHADOW_THICKNESS);
        
        // TODO split on vertex
    }
    
    // TODO above ground
}

#ifdef MT_DEBUG
void Object::draw_visable_box(const Camera * _camera) const {
    if (m_width && m_height) {
        _camera->draw_polygon(Color(BLACK, 64), visable_box(), 2 / _camera->zoom(), m_z);
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

float Object::gravity_ratio() const {
    return m_gravity_ratio;
}

void Object::gravity_ratio(float _gravity_ratio) {
    m_gravity_ratio  = _gravity_ratio;
}

Rectangle Object::visable_box() const {
    return Rectangle(width(), height(), position());
}
