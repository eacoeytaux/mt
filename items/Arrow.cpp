#include "Arrow.hpp"

#include "World.hpp"

NAMESPACES
using mt::exst::Arrow;

const float SHAFT_LENGTH = 32;
const Color TIP_COLOR = GRAY_LIGHT;
const Color SHAFT_COLOR = Color(139, 69, 19);

Arrow::Arrow(World * _world, const Coordinate & tip, const Vector & launch_speed, const Color & _feather_color) :
Object(_world, Matter(tip).velocity(launch_speed)) {
    m_angle = launch_speed.angle();
    m_feather_color = _feather_color;
    gravity_ratio(0.5);
    layer_position(101); // TODO
}

void Arrow::update(float dt) {
    Angle delta = velocity().angle() - m_angle;
//    delta *= 0.75;
    m_angle += delta;
    Object::update(dt);
}

void Arrow::move(float dt) {
    Rectangle delta = Rectangle(position(), position() + (velocity() * dt));
    varray<shared_ptr<Object>> possible_hits = m_world->objects_in_range(delta);
    for_each (possible_hit, possible_hits) {
        if (id() == possible_hit->id()) continue;
        if (dynamic_pointer_cast<Mob>(possible_hit)) dynamic_pointer_cast<Mob>(possible_hit)->hurt(32);
    }
    Object::move(dt);
}

void Arrow::draw(const Camera * _camera) const {
    Angle motion_angle = m_angle;
    
    Coordinate back_pos = position() - Vector(SHAFT_LENGTH, 0);
    Triangle tip = Triangle({ position() + Vector(4, 0), position() + Vector(-4, 4), position() + Vector(-4, -4) });
    Polygon feather = Polygon(varray<Coordinate>({ back_pos + Vector(4, 0), back_pos + Vector(0, 4), back_pos + Vector(-8, 4), back_pos + Vector(-4, 0), back_pos + Vector(-8, -4), back_pos + Vector(0, -4) }));
    
    back_pos.rotate(motion_angle, position());
    tip.rotate(motion_angle, position());
    feather.rotate(motion_angle, position());
    
    _camera->draw_line(SHAFT_COLOR, Line(position(), back_pos), 3);
    _camera->draw_shape(TIP_COLOR, tip);
    _camera->draw_shape(m_feather_color, feather);
    
    Object::draw(_camera);
}
