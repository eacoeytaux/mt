#include "Player.hpp"

#include "World.hpp"
#include "IcePick.hpp"
#include "Arrow.hpp"

NAMESPACES
using mt::exst::Player;

bool Player::god_mode = true;

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
const int RELOAD_TIME = 5;

// graphics
static float BOW_ORIGIN_OFFSET_Y = METER / 4;
static float JACKET_HEAD_OPENING = 0.6;
static float HEAD_RADIUS = METER / 3;
static float NECK_LENGTH = METER / 16;
static float BODY_WIDTH = METER / 1.5;
static float BODY_HEIGHT = METER * 0.8;
static float LEG_WIDTH = METER / 4;
static float LEG_LENGTH = METER / 2;
static float ARM_WIDTH = METER / 5;

static int BLINK_DURATION = 7;
static int MIN_BLINK_GAP = 240;
static int MAX_BLINK_GAP = 300;

const Color SKIN_COLOR = Color(255, 224, 189);
//const Color SKIN_COLOR = Color(124, 80, 26);
const Color HAIR_COLOR = Color(200, 36, 36);
const Color EYE_COLOR = BLACK;

const Color HAT_COLOR = YELLOW;
const Color JACKET_COLOR = Color(139, 69, 19); //Color(255, 190, 0);
const Color JACKET_FRONT_COLOR = JACKET_COLOR; //Color(255, 165, 0);
const Color JACKET_BACK_COLOR = JACKET_COLOR; //Color(255, 130, 0);
const Color UNDERSHIRT_COLOR = WHITE;
const Color PANTS_COLOR = Color(205, 133, 63);
const Color BOOT_COLOR = BLACK;
const Color SOLE_COLOR = GRAY_MID;
const Color LACE_COLOR = WHITE;

const float HANDLE_LENGTH = 12;
const Color CROSSBOW_COLOR = Color(164, 72, 32);

Player::Player(World* _world, const Coordinate & _center) :
Mob(_world, _center, WIDTH, HEIGHT),
m_movement_speed(DEFAULT_SPEED),
m_rope_max_length(DEFAULT_ROPE_MAX_LENGTH),
m_hook_growth_speed(DEFAULT_HOOK_GROWTH_SPEED),
m_hook_retract_speed(DEFAULT_HOOK_RETRACT_SPEED),
m_rope(m_world, position(), DEFAULT_ROPE_MAX_LENGTH, DEFAULT_HOOK_GROWTH_SPEED, DEFAULT_HOOK_RETRACT_SPEED) {
    m_world->camera_target(position(), true);
    health(100);
    m_reload_timer.reset(0);
    layer_position(100); // TODO variablize
#ifdef MT_DEBUG
    god(god_mode);
#endif
}

void Player::adjust_velocity(float dt) {
    if (!m_gravity_ratio) { // can fly?
        if (m_looking_up) {
            if (m_moving_right && !m_moving_left) {
                add_velocity(Vector(Angle(PI * 1/4), m_movement_speed) - Vector(m_movement_speed, 0));
            } else if (m_moving_left && !m_moving_right) {
                add_velocity(Vector(Angle(PI * 3/4), m_movement_speed) - Vector(-m_movement_speed, 0));
            } else {
                add_velocity(Vector(0, m_movement_speed));
            }
        }
        if (m_looking_down) {
            if (m_moving_right && !m_moving_left) {
                add_velocity(Vector(Angle(PI * 7/4), m_movement_speed) - Vector(m_movement_speed, 0));
            } else if (m_moving_left && !m_moving_right) {
                add_velocity(Vector(Angle(PI * 5/4), m_movement_speed) - Vector(-m_movement_speed, 0));
            } else {
                add_velocity(Vector(0, -m_movement_speed));
            }
        }
    }
        
    if (m_moving_right) {
        add_velocity(Vector(m_movement_speed, 0));
    }
    if (m_moving_left) {
        add_velocity(Vector(-m_movement_speed, 0));
    }
    
    Mob::adjust_velocity(dt);
    
    if (m_ground) m_jump_reset_timer.tick();
    if (m_jumping) {
        if (!m_jump_reset_timer.remaining() && m_ground) {
            m_jumping_timer.reset(JUMP_MAX_DURATION);
            m_jump_reset_timer.reset(JUMP_RESET_WAIT_TIME);
            m_jump_degradation = 0;
        }
        
        if (!m_jumping_timer.tick()) {
            add_velocity((Vector(0, JUMP_STRENGTH) - GRAVITY) * (1 - m_jump_degradation));
            m_jump_degradation = 1 - (JUMP_DEGRATION_RATIO * (1 - m_jump_degradation));
            m_ground = nullptr;
        }
    } else {
        m_jumping_timer.reset(0);
    }
    
    velocity(velocity() * 0.9);
}

void Player::move(float dt) {
    Mob::move(dt);
    m_world->camera_target(position());
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

void Player::update(float dt) {
#ifdef MT_DEBUG
    if (god_mode) {
//        m_world->lights(true);
    }
#endif
    Object::update(dt);
    m_world->add_light_source(position(), 100);
    
    m_rope.position(position());
    m_rope.angle(m_aim_angle);
    m_rope.firing(m_firing_hook);
    m_rope.update(dt);
    
    m_reload_timer.tick();
    
    if (m_firing_arrow) {
        if (!m_reload_timer.remaining()) {
            m_world->add_object(shared_ptr<Object>(new Arrow(m_world, position() + Vector(m_aim_angle, 32), Vector(m_aim_angle /* + ((Random::r_Angle() / 16) - PI / 16) */, 32) + velocity())));
            m_reload_timer.reset(RELOAD_TIME);
        }
    }
}

void Player::draw(const Camera * _camera) const {
#ifdef MT_DEBUG
    if (god_mode) {
        static Color glow = Color(WHITE, 32);
        _camera->draw_circle(glow, Circle(METER * 2, position()));
        _camera->draw_circle(glow, Circle(METER * 1.7, position()));
        _camera->draw_circle(glow, Circle(METER * 1.3, position()));
    }
#endif
    
    // draw hook
    m_rope.draw(_camera);
    
    Mob::draw(_camera);
    
    draw_back_leg(_camera);
    draw_back_arm(_camera);
    draw_body(_camera);
    draw_front_leg(_camera);
    draw_head(_camera);
    draw_accessories(_camera);
    draw_front_arm(_camera);
    
#ifdef MT_DEBUG
    if (Debug::on) {
        _camera->draw_rectangle(MAGENTA, visable_box(), 1);
        
        if (!god_mode) { // no boundaries in god mode
            for_each (terrain_edge, m_world->terrain()->edges()) {
                _camera->draw_line(CYAN, terrain_edge->line() + Vector(0, m_height / 2), 1);
            }
        }
        
        _camera->draw_polygon(MAGENTA, Polygon(4, 3 / _camera->zoom(), position()));
        Vector velocity_graphic = velocity();
        velocity_graphic.origin(position());
        velocity_graphic *= 2;
        if (velocity_graphic.magnitude() > 1) {
            _camera->draw_vector(MAGENTA, velocity_graphic, 3, velocity_graphic.magnitude(), 10);
        }
    }
#endif
}

void Player::draw_head(const Camera * _camera) const {
    Coordinate head_center = position() + Vector(0, (BODY_HEIGHT / 2) - BOW_ORIGIN_OFFSET_Y + HEAD_RADIUS - NECK_LENGTH);
    Coordinate face_center = head_center + Vector(m_aim_angle, HEAD_RADIUS * ((1 - JACKET_HEAD_OPENING) / 2));
    
//    _camera->draw_circle(HAT_COLOR, Circle(HEAD_RADIUS * 1.1, head_center - Vector(m_aim_angle, HEAD_RADIUS * 0.2) + Vector(m_aim_angle + (PI / 2), 4)));
    
    _camera->draw_circle(HAIR_COLOR, Circle(HEAD_RADIUS, head_center));
    _camera->draw_circle(SKIN_COLOR, Circle(HEAD_RADIUS * JACKET_HEAD_OPENING, face_center));
    
    // ears
    // _camera->draw_circle(SKIN_COLOR, Circle(2, face_center + Vector(9, 0)));
    // _camera->draw_circle(SKIN_COLOR, Circle(2, face_center + Vector(-9, 0)));
    
    // _camera->draw_circle(WHITE, Circle(HEAD_RADIUS * JACKET_HEAD_OPENING, face_center), 8);
    // _camera->draw_rectangle(WHITE, Rectangle(5, 4, face_center + Vector(5, 0)));
    // _camera->draw_rectangle(WHITE, Rectangle(5, 4, face_center + Vector(-5, 0)));
    
    m_blink_counter.tick();
    if (m_blink_counter.remaining() < BLINK_DURATION) {
        if (!m_blink_counter.remaining()) m_blink_counter.reset(Random::r_int(MIN_BLINK_GAP, MAX_BLINK_GAP));
        _camera->draw_rectangle(EYE_COLOR, Rectangle(3, 1, face_center + Vector(5, -1)));
        _camera->draw_rectangle(EYE_COLOR, Rectangle(3, 1, face_center + Vector(-5, -1)));
    } else {
        _camera->draw_rectangle(EYE_COLOR, Rectangle(3, 3, face_center + Vector(5, 0)));
        _camera->draw_rectangle(EYE_COLOR, Rectangle(3, 3, face_center + Vector(-5, 0)));
    }
    
    _camera->draw_rectangle(HAIR_COLOR, Rectangle(8, 8, face_center + Vector(0, -8)));
    _camera->draw_rectangle(HAIR_COLOR, Rectangle(20, 12, face_center + Vector(0, -12)));
//    _camera->draw_rectangle(HAIR_COLOR, Rectangle(6, 12, face_center + Vector(-12, -5)));
//    _camera->draw_rectangle(HAIR_COLOR, Rectangle(5, 12, face_center + Vector(11, -5)));
    
//    _camera->draw_rectangle(HAIR_COLOR, Rectangle(12, 12, face_center + Vector(0, 10), (PI / 4)));
//    _camera->draw_rectangle(HAIR_COLOR, Rectangle(8, 8, face_center + Vector(6, 10), (PI / 4)));
//    _camera->draw_rectangle(HAIR_COLOR, Rectangle(8, 8, face_center + Vector(-6, 10), (PI / 4)));
    
    Polygon hat = Polygon(varray<Coordinate>({ Coordinate(HEAD_RADIUS * 0.75, HEAD_RADIUS * 1.2), Coordinate(-HEAD_RADIUS * 0.75, HEAD_RADIUS * 1.2), Coordinate(-HEAD_RADIUS, HEAD_RADIUS / 2), Coordinate(HEAD_RADIUS, HEAD_RADIUS / 2) }));
    Line brim = Line(face_center + Coordinate(-HEAD_RADIUS * 1.25, HEAD_RADIUS / 2), face_center + Coordinate(HEAD_RADIUS * 1.25, HEAD_RADIUS / 2));
    hat.move(face_center);
//    _camera->draw_polygon(HAT_COLOR, hat);
//    _camera->draw_line(HAT_COLOR, brim, 4);
}

void Player::draw_body(const Camera * _camera) const {
    //    _camera->draw_rectangle(MID_COLOR, Rectangle(BODY_WIDTH, BODY_HEIGHT, position() + Vector(0, -BOW_ORIGIN_OFFSET_Y)));
    
    // pants base
    _camera->draw_rectangle(PANTS_COLOR, Rectangle(BODY_WIDTH - 4, BODY_HEIGHT * (1.0/3.0), position() + Vector(0, -BOW_ORIGIN_OFFSET_Y + (-BODY_HEIGHT * (1.0/4.0)))));
    
    _camera->draw_line(BLACK, Line(position() + Vector((BODY_WIDTH - 2) / 2, -BOW_ORIGIN_OFFSET_Y - (BODY_HEIGHT * (1.0/4.0)) + 3), position() + Vector(-(BODY_WIDTH - 2) / 2, -BOW_ORIGIN_OFFSET_Y - (BODY_HEIGHT * (1.0/4.0)) + 3)), 4);
    
    // undershirt
    _camera->draw_rectangle(WHITE, Rectangle(BODY_WIDTH * 0.5, BODY_HEIGHT * (2.0/3.0), position() + Vector(0, -BOW_ORIGIN_OFFSET_Y + (BODY_HEIGHT * (1.0/6.0)))));
    
    // jacket
    _camera->draw_rectangle(JACKET_COLOR, Rectangle(BODY_WIDTH / 3, BODY_HEIGHT * (2.0/3.0), position() + Vector(BODY_WIDTH / 3, -BOW_ORIGIN_OFFSET_Y + (BODY_HEIGHT * (1.0/6.0)))));
    _camera->draw_rectangle(JACKET_COLOR, Rectangle(BODY_WIDTH / 3, BODY_HEIGHT * (2.0/3.0), position() + Vector(-BODY_WIDTH / 3.5, -BOW_ORIGIN_OFFSET_Y + (BODY_HEIGHT * (1.0/6.0)))));
}

void Player::draw_front_arm(const Camera * _camera) const {
    Coordinate shoulder_joint_left = position() + Vector(-(BODY_WIDTH / 2) + 4, (BODY_HEIGHT / 2) - BOW_ORIGIN_OFFSET_Y);
    Coordinate hand_left = position() + Vector(m_aim_angle - (PI / 4), HANDLE_LENGTH);
    
    _camera->draw_circle(SKIN_COLOR, Circle(ARM_WIDTH / 2, hand_left));
    
//    Line left_arm = Line(shoulder_joint_left, hand_left);
//    _camera->draw_line(JACKET_FRONT_COLOR, left_arm, ARM_WIDTH);
    
    Joint arm = Joint(shoulder_joint_left, 15, 14, hand_left);
    _camera->draw_line(JACKET_FRONT_COLOR, Line(arm.c1(), arm.joint()), ARM_WIDTH);
    _camera->draw_circle(JACKET_FRONT_COLOR, Circle(ARM_WIDTH / 2, arm.joint()));
    _camera->draw_line(JACKET_FRONT_COLOR, Line(arm.joint(), arm.c2()), ARM_WIDTH);
}

void Player::draw_front_leg(const Camera * _camera) const {
    Coordinate hip_joint_left = position() + Vector(-(BODY_WIDTH / 2) + (LEG_WIDTH / 2) + 3, -(BODY_HEIGHT / 2));
    Coordinate foot_joint_left = position() + Vector(-(BODY_WIDTH / 2) + (LEG_WIDTH / 2) + 3, -(BODY_HEIGHT / 2) - LEG_LENGTH);
    
    if (m_ground && (m_moving_left ^ m_moving_right)) {
        if (m_moving_left) foot_joint_left += Vector((float)((m_world->age() + 8) % 16) - 8, 0);
        else if (m_moving_right) foot_joint_left -= Vector((float)((m_world->age() + 8) % 16) - 8, 0);
    }
    
    Line left_leg = Line(hip_joint_left, foot_joint_left);
    
    Rectangle left_boot_base = Rectangle(LEG_WIDTH + 7, 5, foot_joint_left + Vector(1.5, 0));
    Rectangle left_boot_shin = Rectangle(LEG_WIDTH + 4, 9, foot_joint_left + Vector(0, 2));
    Rectangle left_boot_sole = Rectangle(LEG_WIDTH + 5, 2, foot_joint_left + Vector(1.5, -3));
    Line lace_1 = Line(foot_joint_left + Vector(5, 5), foot_joint_left + Vector(-3, 5));
    Line lace_2 = Line(foot_joint_left + Vector(5, 3), foot_joint_left + Vector(-3, 3));
    
    _camera->draw_line(PANTS_COLOR, left_leg, LEG_WIDTH);
    _camera->draw_rectangle(BOOT_COLOR, left_boot_shin);
    _camera->draw_line(LACE_COLOR, lace_1, 1);
    _camera->draw_line(LACE_COLOR, lace_2, 1);
    _camera->draw_rectangle(SOLE_COLOR, left_boot_sole);
    _camera->draw_rectangle(BOOT_COLOR, left_boot_base);
}

void Player::draw_back_arm(const Camera * _camera) const {
    Coordinate shoulder_joint_right = position() + Vector((BODY_WIDTH / 2) - (ARM_WIDTH / 2) - 4, (BODY_HEIGHT / 2) - (ARM_WIDTH / 2) - BOW_ORIGIN_OFFSET_Y);
    Coordinate hand_right = position() + Vector(m_aim_angle - (PI / 8), 24);
    
    Line right_arm = Line(shoulder_joint_right, hand_right);
    _camera->draw_line(JACKET_BACK_COLOR, right_arm, ARM_WIDTH);
//    _camera->draw_line(JACKET_BACK_COLOR, right_arm, ARM_WIDTH);
    
//    Joint arm = Joint(shoulder_joint_right, 24, 24, hand_right);
//    _camera->draw_line(JACKET_BACK_COLOR, Line(arm.c1(), arm.joint()), ARM_WIDTH);
//    _camera->draw_circle(JACKET_BACK_COLOR, Circle(ARM_WIDTH / 2, arm.joint()));
//    _camera->draw_line(JACKET_BACK_COLOR, Line(arm.joint(), arm.c2()), ARM_WIDTH);
    
    _camera->draw_circle(SKIN_COLOR, Circle(ARM_WIDTH / 2, hand_right));
}

void Player::draw_back_leg(const Camera * _camera) const {
    Coordinate hip_joint_right = position() + Vector((BODY_WIDTH / 2) - (LEG_WIDTH / 2) - 3, -(BODY_HEIGHT / 2));
    Coordinate foot_joint_right = position() + Vector((BODY_WIDTH / 2) - (LEG_WIDTH / 2) - 3, -(BODY_HEIGHT / 2) - LEG_LENGTH);
    
    if (m_ground && (m_moving_left ^ m_moving_right)) {
        if (m_moving_left) foot_joint_right += Vector((float)(m_world->age() % 16) - 8, 0);
        else if (m_moving_right) foot_joint_right -= Vector((float)(m_world->age() % 16) - 8, 0);
    }
    
    Line right_leg = Line(hip_joint_right, foot_joint_right);
    Rectangle right_boot_base = Rectangle(LEG_WIDTH + 7, 5, foot_joint_right + Vector(1.5, 0));
    Rectangle right_boot_shin = Rectangle(LEG_WIDTH + 4, 9, foot_joint_right + Vector(0, 2));
    Rectangle right_boot_sole = Rectangle(LEG_WIDTH + 5, 2, foot_joint_right + Vector(1.5, -3));
    Line lace_1 = Line(foot_joint_right + Vector(5, 5), foot_joint_right + Vector(-3, 5));
    Line lace_2 = Line(foot_joint_right + Vector(5, 3), foot_joint_right + Vector(-3, 3));
    
    _camera->draw_line(PANTS_COLOR, right_leg, LEG_WIDTH);
    _camera->draw_rectangle(BOOT_COLOR, right_boot_shin);
    _camera->draw_line(LACE_COLOR, lace_1, 1);
    _camera->draw_line(LACE_COLOR, lace_2, 1);
    _camera->draw_rectangle(SOLE_COLOR, right_boot_sole);
    _camera->draw_rectangle(BOOT_COLOR, right_boot_base);
}

void Player::draw_accessories(const Camera * _camera) const {
    // draw ice pick
//     static IcePick icepick(m_world, position());
//     icepick.position(position());
//     icepick.draw(_camera);
    
    // draw crossbow
    static bool set = false;
    static Polygon crossbow_static;
    if (!set) {
        float scale = 5;
        crossbow_static = Polygon({ Coordinate(6 * scale, 0 * scale), Coordinate(0 * scale, 0 * scale), Coordinate(-2 * scale, -2 * scale), Coordinate(-4 * scale, -2 * scale), Coordinate(-4 * scale, -4 * scale), Coordinate(1 * scale, -1 * scale), Coordinate(5 * scale, -1 * scale) });
        set = true;
    }
    Polygon crossbow = crossbow_static;
    crossbow.move(position());
    crossbow.rotate_about(m_aim_angle, position());
    Line crossbow_handle = Line(position() + Vector(22, 0), position() + Vector(22, -HANDLE_LENGTH));
    crossbow_handle.rotate_around_origin(m_aim_angle, position());
    _camera->draw_polygon(CROSSBOW_COLOR, crossbow);
    _camera->draw_line(CROSSBOW_COLOR, crossbow_handle, 4);
    
    static Color feather_color = MAGENTA; //Random::r_Color();
    Arrow arrow = Arrow(m_world, position() + Vector(m_aim_angle, 32), Vector(m_aim_angle, 1), feather_color);
    arrow.draw(_camera);
}

void Player::draw_reticle(const Camera * _camera) const {
    if (m_aiming) {
        _camera->draw_rectangle(BLACK, Rectangle((RETICLE_LENGTH + 2) / _camera->zoom(), (RETICLE_WIDTH + 2) / _camera->zoom(), position() + Vector(m_aim_angle, RETICLE_DISTANCE)), 0);
        _camera->draw_rectangle(BLACK, Rectangle((RETICLE_WIDTH + 2) / _camera->zoom(), (RETICLE_LENGTH + 2) / _camera->zoom(), position() + Vector(m_aim_angle, RETICLE_DISTANCE)), 0);
        
        _camera->draw_rectangle(WHITE, Rectangle(RETICLE_WIDTH / _camera->zoom(), RETICLE_LENGTH / _camera->zoom(), position() + Vector(m_aim_angle, RETICLE_DISTANCE)), 0);
        _camera->draw_rectangle(WHITE, Rectangle(RETICLE_LENGTH / _camera->zoom(), RETICLE_WIDTH / _camera->zoom(), position() + Vector(m_aim_angle, RETICLE_DISTANCE)), 0);
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

void Player::fire_arrow() {
    m_firing_arrow = true;
}

void Player::release_bow() {
    m_firing_hook = false;
    m_firing_arrow = false;
}

#ifdef MT_DEBUG

bool Player::god() const {
    return god_mode;
}

void Player::god(bool _b) {
    god_mode = _b;
    
    if (god_mode) {
        gravity_ratio(0);
        terrarin_boundaries(false);
        velocity(Vector(0, 0)); // god brings all to a halt
    } else {
        gravity_ratio(1);
        terrarin_boundaries(true);
    }
}

#endif
