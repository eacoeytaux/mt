#include "Rope.hpp"

NAMESPACES
using mt::exst::Rope;

const int ROPE_WIDTH = 4;
const int HOOK_WIDTH = 6;
const int HOOK_LENGTH = 24;
const int HOOK_HEAD_LENGTH = 16;
const int HOOK_OUTLINE_THICKNESS = ROPE_WIDTH;
const Angle HOOK_ANGLE = Angle(PI / 4);
const Color ROPE_BASE_COLOR = Color(218, 165, 32);
const Color ROPE_ALT_COLOR = Color(184, 134, 11);
const Color HOOK_COLOR = Color(156, 156, 156);

Rope::Rope(World* _world, const Coordinate & _center, float _max_length, float _growth_speed, float _retract_speed) :
Object(_world, _center),
m_angle(Angle(PI / 4)),
m_length(0),
m_max_length(_max_length),
m_growth_speed(_growth_speed),
m_retract_speed(_retract_speed) {
    
}

void Rope::update(float dt) {
    if (m_firing) {
        if (m_length < m_max_length) {
            m_length += m_growth_speed;
            m_length = min(m_length, m_max_length);
        }
    } else {
        if (m_length) {
            m_length -= m_retract_speed;
            m_length = max<float>(m_length, 0);
        }
    }
}

void Rope::adjust_velocity(float dt) {
    Object::adjust_velocity(dt);
}

void Rope::move(float dt) {
    Object::move(dt);
}

void Rope::draw(const Camera * _camera) const {
    if (!length()) return;

    // set up variables
    Vector rope_vector(angle(), length(),  position());
//        Vector rope_vector_half(m_angle, m_length / 2, m_center);
    
    // draw hook
    _camera->draw_circle(HOOK_COLOR, Circle(HOOK_OUTLINE_THICKNESS * 1.5, hook_position()));
    _camera->draw_line(HOOK_COLOR, Line(hook_position(), hook_position() + Vector(angle(), HOOK_LENGTH)), HOOK_WIDTH);
    _camera->draw_square(HOOK_COLOR, Square(HOOK_WIDTH, hook_position() + Vector(angle(), HOOK_LENGTH), angle() + (PI / 4)));
    
    _camera->draw_line(HOOK_COLOR, Line(hook_position() + Vector(angle(), HOOK_LENGTH), hook_position() + Vector(angle(), HOOK_LENGTH) + Vector(angle() + (PI * 0.64), HOOK_HEAD_LENGTH)), HOOK_WIDTH);
    _camera->draw_line(HOOK_COLOR, Line(hook_position() + Vector(angle(), HOOK_LENGTH), hook_position() + Vector(angle(), HOOK_LENGTH) + Vector(angle() - (PI * 0.64), HOOK_HEAD_LENGTH)), HOOK_WIDTH);
    
    // draw rope base
    _camera->draw_line(ROPE_BASE_COLOR, Line(rope_vector.origin(), rope_vector.destination()), ROPE_WIDTH);
    
    // draw rope detail coils
    Vector rope_chunk(m_angle, ROPE_WIDTH);
    for_range (length() / ROPE_WIDTH / 2) {
        Rectangle rope_strip_rect(ROPE_WIDTH, ROPE_WIDTH, hook_position() - (rope_chunk * i * 2), angle());
        _camera->draw_rectangle(ROPE_ALT_COLOR, rope_strip_rect);
    }
}

Coordinate Rope::hook_position() const {
    return position() + Vector(angle(), length());
}

bool Rope::firing() const {
    return m_firing;
}

void Rope::firing(bool _firing) {
    m_firing = _firing;
}

Angle Rope::angle() const {
    return m_angle;
}

void Rope::angle(const Angle & _angle) {
    m_angle = _angle;
}

float Rope::length() const {
    return m_length;
}

void Rope::length(float _length) {
    m_length = _length;
}

float Rope::max_length() const {
    return m_max_length;
}

void Rope::max_length(float _max_length) {
    m_max_length = _max_length;
}
