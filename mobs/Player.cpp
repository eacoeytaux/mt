#include "Player.hpp"

#include "World.hpp"

using namespace mt;

const float WIDTH = 1.5 * METER;
const float HEIGHT = 2 * METER;
const float DEFAULT_SPEED = 1.0;
const float JUMP_STRENGTH = (1.0/3.0) * METER;
const float JUMP_DEGRATION_RATIO = 0.9;
const int JUMP_MAX_DURATION = 5;
const int JUMP_RESET_WAIT_TIME = 0;
const float RETICLE_DISTANCE = WIDTH * 2;
const float RETICLE_WIDTH = 1;
const float RETICLE_LENGTH = 9;
const float DEFAULT_ROPE_MAX_LENGTH = HEIGHT * 3;
const float DEFAULT_HOOK_GROWTH_SPEED = 20;
const float DEFAULT_HOOK_RETRACT_SPEED = 30;

Player::Player(World* _world, const Coordinate & _center) :
Mob(_world, _center, WIDTH, HEIGHT),
m_movement_speed(DEFAULT_SPEED),
m_rope_max_length(DEFAULT_ROPE_MAX_LENGTH),
m_hook_growth_speed(DEFAULT_HOOK_GROWTH_SPEED),
m_hook_retract_speed(DEFAULT_HOOK_RETRACT_SPEED),
m_rope(_world, m_center, DEFAULT_ROPE_MAX_LENGTH, DEFAULT_HOOK_GROWTH_SPEED, DEFAULT_HOOK_RETRACT_SPEED) {
    _world->camera_target(m_center, true);
    health(100);
}

void Player::update_velocity() {
    if (!m_gravity_affected) { // can fly?
        if (m_looking_up) {
            if (m_moving_right && !m_moving_left) {
                m_velocity += Vector(Angle(PI * 1/4), m_movement_speed) - Vector(m_movement_speed, 0);
            } else if (m_moving_left && !m_moving_right) {
                m_velocity += Vector(Angle(PI * 3/4), m_movement_speed) - Vector(-m_movement_speed, 0);
            } else {
                m_velocity += Vector(0, m_movement_speed);
            }
        }
        if (m_looking_down) {
            if (m_moving_right && !m_moving_left) {
                m_velocity += Vector(Angle(PI * 7/4), m_movement_speed) - Vector(m_movement_speed, 0);
            } else if (m_moving_left && !m_moving_right) {
                m_velocity += Vector(Angle(PI * 5/4), m_movement_speed) - Vector(-m_movement_speed, 0);
            } else {
                m_velocity += Vector(0, -m_movement_speed);
            }
        }
    }
        
    if (m_moving_right) {
        m_velocity += Vector(m_movement_speed, 0);
    }
    if (m_moving_left) {
        m_velocity += Vector(-m_movement_speed, 0);
    }
    
    Mob::update_velocity();
    
    
    if (m_ground) m_jump_reset_timer.tick();
    if (m_jumping) {
        if (!m_jump_reset_timer.remaining() && m_ground) {
            m_jumping_timer.reset(JUMP_MAX_DURATION);
            m_jump_reset_timer.reset(JUMP_RESET_WAIT_TIME);
            m_jump_degradation = 0;
        }
        
        if (!m_jumping_timer.tick()) {
            m_velocity += (Vector(0, JUMP_STRENGTH) - GRAVITY) * (1 - m_jump_degradation);
            m_jump_degradation = 1 - (JUMP_DEGRATION_RATIO * (1 - m_jump_degradation));
            m_ground = nullptr;
        }
    } else {
        m_jumping_timer.reset(0);
    }
    
    m_velocity *= 0.9;
}

void Player::move(const Vector & _vector) {
    Mob::move(_vector);
    m_world->camera_target(center());
}

void Player::kill() {
#ifdef MT_DEBUG
    if (god_mode) return;
#endif
    Mob::kill();
}

void Player::hurt(int _health) {
#ifdef MT_DEBUG
    if (god_mode) return;
#endif
    Mob::hurt(_health);
}

void Player::update() {
#ifdef MT_DEBUG
    if (god_mode) {
//        m_world->lights(true);
    }
#endif
    Object::update();
    m_world->add_light_source(center(), 100);
    
    m_rope.center(m_center);
    m_rope.angle(m_aim_angle);
    m_rope.firing(m_firing_hook);
    m_rope.update();
}

void Player::draw(const Camera & _camera) const {
    // draw hook
    m_rope.draw(_camera);
    
    Mob::draw(_camera);
    
    // draw character
    _camera.draw_rectangle(YELLOW, Rectangle(m_width, m_height, m_center));
    
#ifdef MT_DEBUG
    if (Debug::on) {
        if (!god_mode) { // no boundaries in god mode
            for_each (terrain_edge, m_world->terrain().edges()) {
                _camera.draw_line(CYAN, terrain_edge->line() + Vector(0, m_height / 2), 1);
            }
        }
        
        _camera.draw_polygon(MAGENTA, Polygon(4, 3 / _camera.zoom(), m_center));
        Vector velocity_graphic = m_velocity;
        velocity_graphic.origin(m_center);
        velocity_graphic *= 2;
        if (velocity_graphic.magnitude() > 1) {
            _camera.draw_vector(MAGENTA, velocity_graphic, 3, velocity_graphic.magnitude(), 10);
        }
    }
#endif
}

void Player::draw_reticle(const Camera & _camera) const {
    if (m_aiming) {
        _camera.draw_rectangle(BLACK, Rectangle((RETICLE_LENGTH + 2) / _camera.zoom(), (RETICLE_WIDTH + 2) / _camera.zoom(), m_center + Vector(m_aim_angle, RETICLE_DISTANCE)), 0);
        _camera.draw_rectangle(BLACK, Rectangle((RETICLE_WIDTH + 2) / _camera.zoom(), (RETICLE_LENGTH + 2) / _camera.zoom(), m_center + Vector(m_aim_angle, RETICLE_DISTANCE)), 0);
        
        _camera.draw_rectangle(WHITE, Rectangle(RETICLE_WIDTH / _camera.zoom(), RETICLE_LENGTH / _camera.zoom(), m_center + Vector(m_aim_angle, RETICLE_DISTANCE)), 0);
        _camera.draw_rectangle(WHITE, Rectangle(RETICLE_LENGTH / _camera.zoom(), RETICLE_WIDTH / _camera.zoom(), m_center + Vector(m_aim_angle, RETICLE_DISTANCE)), 0);
    }
}

void Player::moving_right(bool _moving) {
    m_moving_right = _moving;
}

void Player::moving_left(bool _moving) {
    m_moving_left = _moving;
}

void Player::looking_up(bool _looking) {
    m_looking_up = _looking;
}

void Player::looking_down(bool _looking) {
    m_looking_down = _looking;
}

void Player::jump(bool _jumping) {
    m_jumping = _jumping;
}

void Player::aim(const Angle & _aim_angle) {
    m_aim_angle = _aim_angle;
}

void Player::fire_hook() {
    m_firing_hook = true;
}

void Player::retract_hook() {
    m_firing_hook = false;
}

#ifdef MT_DEBUG

bool Player::god() const {
    return god_mode;
}

void Player::god(bool _b) {
    god_mode = _b;
    
    if (god_mode) {
        gravity_affected(false);
        terrarin_boundaries(false);
        velocity(Vector(0, 0)); // god brings all to a halt
    } else {
        gravity_affected(true);
        terrarin_boundaries(true);
    }
}

#endif
