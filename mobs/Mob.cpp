#include "Mob.hpp"

NAMESPACES
using mt::exst::Mob;

Mob::Mob(World* _world, const Coordinate & _center, const float _width, const float _height) : Object(_world, _center, _width, _height) { }

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
#ifdef MT_DEBUG
    if (Debug::on) {
        // draw health bar
        const int border_outline_thickness = 1;
        float health_width = width() * 0.8;
        float health_height = health_width / 10;
        Vector offset = Vector(0, ((height() / 2) * 1.2) + health_height);
        float percentage = m_health.percentage();
        _camera->draw_rectangle(WHITE, Rectangle(health_width + (border_outline_thickness * 2), health_height + (border_outline_thickness * 2), position() - offset));
        if (percentage == 1) {
            _camera->draw_rectangle(GREEN, Rectangle(health_width, health_height, position() - offset));
        } else {
            _camera->draw_rectangle(RED, Rectangle(health_width, health_height, position() - offset));
            offset += Vector((health_width / 2) - ((health_width / 2) * percentage) + 1, 0);
            _camera->draw_rectangle(GREEN, Rectangle((int)(health_width * percentage), health_height, position() - offset));
        }
    }
#endif
}

bool Mob::alive() const {
    return m_alive;
}

void Mob::kill() {
    m_health.value(0);
    m_alive = false;
}

int Mob::health() const {
    return m_health.value();
}

void Mob::health(int _health) {
    if (_health > m_health.max()) m_health = Slider<int>(_health);
    m_health.value(_health);
}

void Mob::health(float _percentage) {
    m_health.percentage(_percentage);
}

void Mob::heal(int _health) {
    int new_health = m_health.value();
    new_health += _health;
    new_health = max<int>(new_health, m_health.max());
    m_health.value(new_health);
}

void Mob::heal_full() {
    m_health.value(m_health.max());
}

void Mob::hurt(int _health) {
    int new_health = m_health.value();
    new_health -= _health;
    if (new_health <= 0) {
        m_health.value(0);
        kill();
    } else {
        m_health.value(new_health);
    }
}

int Mob::max_health() const {
    return m_health.max();
}

void Mob::max_health(int _health) {
    m_health = Slider<int>(_health);
}
