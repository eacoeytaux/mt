#include "Object.hpp"

#include "World.hpp"
#include "Terrain.hpp"

NAMESPACES
using mt::exst::Object;

const float SHADOW_ALPHA = 64;
const float SHADOW_WIDTH_SCALE = 0.36; // (0, 1]
const float SHADOW_THICKNESS = 4;

#ifdef MT_DEBUG
const float VELOCITY_SCALE = 3;
const float HIT_BOX_THICKNESS = 1;
const Color HIT_BOX_COLOR = YELLOW;
const float VISABLE_BOX_THICKNESS = 1;
const Color VISABLE_BOX_COLOR = RED;
#endif

static uint64_t total_ids = 0;

Object::Object(World * _world, const Matter & _matter, const float _z) :
Matter(_matter),
m_id(total_ids++) {
    m_world = _world;
    z(_z);
    
    // defaults
//    layer_position(1);
    m_terrarin_boundaries = true;
}

void Object::update_object(float dt) {
    update(dt);
}
    
void Object::update(float dt) {
    update_move(dt);
}

void Object::update_move(float dt) {
    move(dt);
}

void Object::adjust_velocity(float dt) {
    Vector velocity = Matter::velocity();
    
    if (m_ground && m_terrarin_boundaries) {
        Angle ground_angle = m_ground->line().angle();
        velocity.rotate(ground_angle * -1);
        velocity.dy(0);
        velocity.rotate(ground_angle);
    } else if (!m_ground && m_gravity_ratio) {
        velocity += (GRAVITY * m_gravity_ratio);
    }
    
    velocity *= 1 - friction_resistance();
    
    Matter::velocity(velocity);
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
            if (movement_line.intersects(terrain_edge->line() + Vector(0, space().height() / 2))) {
                next_ground = terrain_edge;
                Coordinate intersection = movement_line.intersection(terrain_edge->line() + Vector(0, space().height() / 2));
                movement = Vector(center, intersection);
                movement_percentage = 0;
                if (movement.magnitude()) movement_percentage = movement.magnitude() / velocity.magnitude();
                remaining = velocity - movement;
                remaining.rotate(terrain_edge->line().angle() * -1);
                remaining.dy(0);
                remaining.rotate(terrain_edge->line().angle());
                remaining *= (1 - movement_percentage);
                remaining /= dt;
                Object::velocity();
            }
        }
    }
    
    if (m_ground && next_ground == m_ground) {
        if ((velocity.dx() > 0) && (center + velocity).x() > m_ground->line().right().x()) {
            movement = m_ground->vertex2()->position() - center + Vector(0, space().height() / 2);
            movement_percentage = 0;
            if (movement.magnitude())
                movement_percentage = movement.magnitude() / velocity.magnitude();
            remaining = velocity - movement;
            if (m_ground->vertex2()->edge2()) {
                next_ground = m_ground->vertex2()->edge2();
                remaining.rotate(next_ground->line().angle() * -1);
                remaining.dy(0);
                remaining.rotate(next_ground->line().angle());
            } else {
                next_ground = nullptr;
            }
            remaining *= (1 - movement_percentage);
            remaining /= dt;
            Object::velocity();
        } else if ((velocity.dx() < 0) && (center + velocity).x() < m_ground->line().left().x()) {
            movement = m_ground->vertex1()->position() - center + Vector(0, space().height() / 2);
            movement_percentage = 0;
            if (movement.magnitude())
                movement_percentage = movement.magnitude() / velocity.magnitude();
            remaining = velocity - movement;
            if (m_ground->vertex1()->edge1()) {
                next_ground = m_ground->vertex1()->edge1();
                remaining.rotate(next_ground->line().angle() * -1);
                remaining.dy(0);
                remaining.rotate(next_ground->line().angle());
            } else {
                next_ground = nullptr;
            }
            remaining *= (1 - movement_percentage);
            remaining /= dt;
            Object::velocity();
        }
    }
    
    m_ground = next_ground;
    position(position() + movement);
    
    if (float_gt(movement_percentage, 0)) {
        move(dt * movement_percentage);
    }
}

float Object::friction_resistance() const {
    if (m_terrarin_boundaries && m_ground) {
        return m_ground->resistance();
    }
    return AIR_RESISTANCE;
}

void Object::draw_object(const Camera * _camera) const {
    draw(_camera);
}

void Object::draw(const Camera * _camera) const {
    return;
}

#ifdef MT_DEBUG
void Object::draw_debug(const Camera * _camera) const {
    draw_visible_box(_camera);
    draw_hit_box(_camera);
    // center
    _camera->draw_shape(HIT_BOX_COLOR, Circle((VISABLE_BOX_THICKNESS * 2 / _camera->zoom()), position()));
    // velocity
    Vector velocity_graphic = velocity().origin(position()) * VELOCITY_SCALE;
    if (velocity_graphic.magnitude() > 1) _camera->draw_vector(HIT_BOX_COLOR, velocity_graphic, HIT_BOX_THICKNESS, velocity_graphic.magnitude(), 10);
}

void Object::draw_hit_box(const Camera * _camera) const {
    if (hit_box().area()) {
        _camera->draw_shape(HIT_BOX_COLOR, hit_box(), HIT_BOX_THICKNESS);
    }
}

void Object::draw_visible_box(const Camera * _camera) const {
    if (visible_box().area()) {
        _camera->draw_shape(VISABLE_BOX_COLOR, visible_box(), VISABLE_BOX_THICKNESS);
    }
}
#endif

float Object::width() const {
    return space().width();
}

float Object::height() const {
    return space().height();
}

float Object::z() const {
    return m_z;
}

void Object::z(const float _z) {
    m_z = _z;
}

float Object::visible_width() const {
    return m_visible_width;
}

void Object::visible_width(const float _visible_width) {
    m_visible_width = _visible_width;
}

float Object::visible_height() const {
    return m_visible_height;
}

void Object::visible_height(const float _visible_height) {
    m_visible_height = _visible_height;
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

Rectangle Object::hit_box() const {
    return space();
}

Rectangle Object::visible_box() const {
    return Rectangle(visible_width(), visible_height(), position());
}
