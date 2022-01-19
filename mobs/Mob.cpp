#include "Mob.hpp"

NAMESPACES
using mt::exst::Mob;

Mob::Mob(World * _world, const Coordinate & _center, const float _width, const float _height, const uint _health = 1) : Object(_world, Matter(_center, { Rectangle(_width, _height) })) {
    health(_health);
}

void Mob::update(float dt) {
    Object::update(dt);
}

void Mob::adjust_velocity(float dt) {
    Object::adjust_velocity(dt);
}

void Mob::move(float dt) {
    Object::move(dt);
}

void Mob::draw(const Camera * _camera) const {
    Object::draw(_camera);
}

#ifdef MT_DEBUG
void Mob::draw_debug(const Camera * _camera) const {
    // draw health bar
    const int border_outline_thickness = 1;
    float health_width = space().width() * 0.8;
    float health_height = health_width / 10;
    Vector offset = Vector(0, ((space().height() / 2) * 1.2) + health_height);
    float percentage = m_health.percentage();
    _camera->draw_shape(WHITE, Rectangle(health_width + (border_outline_thickness * 2), health_height + (border_outline_thickness * 2), position() - offset));
    if (alive()) {
        if (percentage == 1) {
            _camera->draw_shape(GREEN, Rectangle(health_width, health_height, position() - offset));
        } else {
            _camera->draw_shape(RED, Rectangle(health_width, health_height, position() - offset));
            offset += Vector((health_width / 2) - ((health_width / 2) * percentage) + 1, 0);
            _camera->draw_shape(GREEN, Rectangle((int)(health_width * percentage), health_height, position() - offset));
        }
    } else {
        _camera->draw_shape(BLACK, Rectangle(health_width, health_height, position() - offset));
        
    }
    Object::draw_debug(_camera);
}
#endif
    
bool Mob::alive() const {
    return m_alive;
}

void Mob::kill() {
    m_health.value(0);
    m_alive = false;
}

uint Mob::health() const {
    return m_health.value();
}

void Mob::health(uint _health) {
    if (_health > m_health.max()) m_health = Slider<uint>(_health);
    m_health.value(_health);
}

void Mob::health(float _percentage) {
    m_health.percentage(_percentage);
}

void Mob::heal(uint _health) {
    int new_health = m_health.value();
    new_health += _health;
    new_health = max<int>(new_health, m_health.max());
    m_health.value(new_health);
}

void Mob::heal_full() {
    m_health.value(m_health.max());
}

void Mob::hurt(uint _health) {
    uint health = Mob::health() - min(_health, Mob::health());
    if (health == 0) {
        m_health.value(0);
        kill();
    } else {
        m_health.value(health);
    }
}

uint Mob::max_health() const {
    return m_health.max();
}

void Mob::max_health(uint _health) {
    m_health = Slider<uint>(_health);
}
