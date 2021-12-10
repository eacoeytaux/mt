#include "Rope.hpp"

using namespace mt;

const int ROPE_WIDTH = 4;
const int HOOK_WIDTH = 6;
const int HOOK_LENGTH = 16;
const int HOOK_OUTLINE_THICKNESS = ROPE_WIDTH;
const Angle HOOK_ANGLE = Angle(PI / 4);
const Color ROPE_BASE_COLOR = Color(218, 165, 32);
const Color ROPE_ALT_COLOR = Color(184, 134, 11);
const Color HOOK_COLOR = Color(184, 184, 184);
const Color HOOK_OUTLINE_COLOR = Color(156, 156, 156);

Rope::Rope(World* _world, const Coordinate & _center, float _max_length, float _growth_speed, float _retract_speed) :
Object(_world, _center),
m_angle(Angle(PI / 4)),
m_length(0),
m_max_length(_max_length),
m_growth_speed(_growth_speed),
m_retract_speed(_retract_speed) {
    
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

void Rope::update() {
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

void Rope::draw(const Camera & _camera) const {
    if (!m_length) return;

    // set up variables
    Vector rope_vector(m_angle, m_length, m_center);
//        Vector rope_vector_half(m_angle, m_length / 2, m_center);
    
    // draw rope base
//        Rectangle rope_rect(m_length, ROPE_WIDTH, m_center + rope_vector_half, m_angle);
//        camera.draw_rectangle(rope_rect, ROPE_BASE_COLOR);
    _camera.draw_line(ROPE_BASE_COLOR, Line(rope_vector.origin(), rope_vector.destination()), ROPE_WIDTH);
    
    // draw rope detail coils
    Vector rope_chunk(m_angle, ROPE_WIDTH);
    for_range (m_length / ROPE_WIDTH / 2) {
        Rectangle rope_strip_rect(ROPE_WIDTH, ROPE_WIDTH, m_center + (rope_chunk * i * 2), m_angle);
        _camera.draw_rectangle(ROPE_ALT_COLOR, rope_strip_rect);
    }
    
    // draw hook
    // draw outline
    _camera.draw_circle(HOOK_OUTLINE_COLOR, Circle(HOOK_WIDTH + HOOK_OUTLINE_THICKNESS, rope_vector.destination()));
    Rectangle hook_base_outline_rect(HOOK_LENGTH + (HOOK_OUTLINE_THICKNESS * 2), HOOK_WIDTH + (HOOK_OUTLINE_THICKNESS * 2), (rope_vector - Vector(m_angle, HOOK_WIDTH / 2)).destination(), m_angle);
    _camera.draw_rectangle(HOOK_OUTLINE_COLOR, hook_base_outline_rect);
    
//        Rectangle hook_right_outline_rect(HOOK_LENGTH + (HOOK_OUTLINE_THICKNESS * 2), HOOK_WIDTH + (HOOK_OUTLINE_THICKNESS * 2), (rope_vector - Vector(m_angle + HOOK_ANGLE, HOOK_WIDTH / 2)).destination(), m_angle + HOOK_ANGLE);
//        Rectangle hook_left_outline_rect(HOOK_LENGTH + (HOOK_OUTLINE_THICKNESS * 2), HOOK_WIDTH + (HOOK_OUTLINE_THICKNESS * 2), (rope_vector - Vector(m_angle - HOOK_ANGLE, HOOK_WIDTH / 2)).destination(), m_angle - HOOK_ANGLE);
//        _camera.draw_rectangle(hook_right_outline_rect, HOOK_OUTLINE_COLOR);
//        _camera.draw_rectangle(hook_left_outline_rect, HOOK_OUTLINE_COLOR);
    
    // draw base
    _camera.draw_circle(HOOK_COLOR, Circle(HOOK_WIDTH, rope_vector.destination()));
    Rectangle hook_base_rect(HOOK_LENGTH, HOOK_WIDTH, (rope_vector - Vector(m_angle, HOOK_WIDTH / 2)).destination(), m_angle);
    _camera.draw_rectangle(HOOK_COLOR, hook_base_rect);
    
//        Rectangle hook_right_rect(HOOK_LENGTH, HOOK_WIDTH, (rope_vector - Vector(m_angle + HOOK_ANGLE, HOOK_WIDTH / 2)).destination(), m_angle + HOOK_ANGLE);
//        Rectangle hook_left_rect(HOOK_LENGTH, HOOK_WIDTH, (rope_vector - Vector(m_angle - HOOK_ANGLE, HOOK_WIDTH / 2)).destination(), m_angle - HOOK_ANGLE);
//        _camera.draw_rectangle(hook_right_rect, HOOK_COLOR);
//        _camera.draw_rectangle(hook_left_rect, HOOK_COLOR);
}
