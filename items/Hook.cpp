#include "Hook.hpp"

NAMESPACES
using mt::exst::Hook;

const int HOOK_LENGTH = 24;
const int HOOK_HEAD_LENGTH = 16;
const int HOOK_THICKNESS = 5;
const Angle HOOK_ANGLE = Angle(PI / 4);
const Color HOOK_COLOR = Color(156, 156, 156);

const int ROPE_WIDTH = 4;
const Color ROPE_BASE_COLOR = Color(218, 165, 32);
const Color ROPE_ALT_COLOR = Color(184, 134, 11);

Hook::Hook(World * _world, const Coordinate & _hook_tip, const Coordinate & _base, const Angle & _angle) : Object(_world, Matter(_hook_tip, {})) {
    m_base = _base;
    m_angle = _angle;
}

Angle Hook::angle() const {
    return m_angle;
}

Hook & Hook::angle(const Angle & _angle) {
    m_angle = _angle;
    return *this;
}

Coordinate Hook::hook_tip() const {
    return position();
}

Coordinate Hook::hook_base() const {
    if (m_state == LOADED) {
        return hook_tip() - Vector(angle(), HOOK_LENGTH);
    } else {
        return hook_tip() - Vector(base(), hook_tip()).magnitude(HOOK_LENGTH);
    }
}

Coordinate Hook::base() const {
    return m_base;
}
    
Hook & Hook::base(const Coordinate & _base, const Angle & _angle) {
    m_base = _base;
    if (m_state == LOADED) {
        angle(_angle);
        position(_base + Vector(angle(), HOOK_LENGTH));
    }
    return *this;
}

float Hook::length() const {
    return m_length;
}

void Hook::length(float _length) {
    m_length = _length;
}

float Hook::max_length() const {
    return m_max_length;
}

void Hook::max_length(float _max_length) {
    m_max_length = _max_length;
}

Hook & Hook::fire(const Vector & _launch_speed) {
    switch (m_state) {
        case LOADED:
            velocity(_launch_speed);
            m_state = FIRING;
            break;
        case FIRING:
        case HOOKED:
        case RETRACTING:
            break;
        default:
            Assert::soft(false, "invalid_state");
            break;
    }
    
    return *this;
}

Hook & Hook::retract() {
    switch (m_state) {
        case LOADED:
            break;
        case FIRING:
        case HOOKED:
            m_state = RETRACTING;
            break;
        case RETRACTING:
            break;
        default:
            Assert::soft(false, "invalid_state");
            break;
    }
    
    return *this;
}

Hook & Hook::load() {
    m_state = LOADED;
    m_ground = nullptr;
    return *this;
}

void Hook::update(float dt) {
    if (m_state == LOADED) {
        gravity_ratio(0);
        velocity(Vector(0, 0));
    } else {
        gravity_ratio(0.0);
        if (m_state == FIRING) {
            length(base().distance(position()));
            if (length() > max_length()) {
                m_state = RETRACTING;
                float percentage = dt; // TODO adjust for overshot
                update(percentage);
            }
        } else if (m_state == RETRACTING) {
//            gravity_ratio(0.25);
            length(length() - m_retract_speed);
            if (length() <= 0) m_state = LOADED;
            else position(Vector(base(), position()).magnitude(length()).destination());
        }
    }
    
    Angle delta;
    if (velocity().magnitude()) delta = velocity().angle() - m_angle;
    m_angle = Vector(base(), hook_tip()).angle();
    
    Object::update(dt);
}

void Hook::draw(const Camera * _camera) const {
    draw_hook(_camera);
    Object::draw(_camera);
}

void Hook::draw_hook(const Camera * _camera) const {
    Coordinate tip = Hook::hook_tip();
    Coordinate base = Hook::hook_base();
    Angle hook_angle = Vector(base, tip).angle();
    
    _camera->draw_shape(HOOK_COLOR, Circle(HOOK_THICKNESS, base));
    _camera->draw_shape(HOOK_COLOR, Square(HOOK_THICKNESS, tip, hook_angle + (PI / 4)));
    _camera->draw_line(HOOK_COLOR, Line(tip, base), HOOK_THICKNESS);
    
    _camera->draw_line(HOOK_COLOR, Line(tip, tip + Vector(hook_angle + (PI * 0.64), HOOK_HEAD_LENGTH)), HOOK_THICKNESS);
    _camera->draw_line(HOOK_COLOR, Line(tip, tip + Vector(hook_angle - (PI * 0.64), HOOK_HEAD_LENGTH)), HOOK_THICKNESS);
}
    
void Hook::draw_rope(const Camera * _camera) const {
    Vector rope_vector(base(), hook_base());
    // draw rope base
    _camera->draw_line(ROPE_BASE_COLOR, Line(rope_vector.origin(), rope_vector.destination()), ROPE_WIDTH);
    // draw rope detail coils
    Vector rope_chunk(rope_vector.angle(), ROPE_WIDTH);
    for_range (rope_vector.magnitude() / ROPE_WIDTH / 2) {
        Rectangle rope_strip_rect(ROPE_WIDTH, ROPE_WIDTH, hook_base() - (rope_chunk * i * 2), rope_chunk.angle());
        _camera->draw_shape(ROPE_ALT_COLOR, rope_strip_rect);
    }
}
