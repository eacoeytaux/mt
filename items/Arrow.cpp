#include "Arrow.hpp"

NAMESPACES
using mt::exst::Arrow;

const Color TIP_COLOR = GRAY_LIGHT;
const Color SHAFT_COLOR = Color(139, 69, 19);

Arrow::Arrow(World* _world, const Coordinate & tip, const Vector & launch_speed) :
Object(_world, tip, 0, 0, 1, launch_speed) {
    m_feather_color = Random::r_Color();
    gravity_ratio(0.5);
    layer_position(101); // TODO
}

void Arrow::update(float dt) {
    Object::update(dt);
}

void Arrow::draw(const Camera * _camera) const {
    Angle motion_angle = velocity().angle();
    
    Coordinate back_pos = position() - Vector(32, 0);
    // TODO triangle isn't working?
    Polygon tip = Polygon(Triangle({ position() + Vector(4, 0), position() + Vector(-4, 4), position() + Vector(-4, -4) }));
    Polygon feather = Polygon(varray<Coordinate>({ back_pos + Vector(4, 0), back_pos + Vector(0, 4), back_pos + Vector(-8, 4), back_pos + Vector(-4, 0), back_pos + Vector(-8, -4), back_pos + Vector(0, -4) }));
    
    back_pos.rotate_about(motion_angle, position());
    tip.rotate_about(motion_angle, position());
    feather.rotate_about(motion_angle, position());
    
    _camera->draw_line(SHAFT_COLOR, Line(position(), back_pos), 3);
    _camera->draw_polygon(TIP_COLOR, tip);
    _camera->draw_polygon(m_feather_color, feather);
}
