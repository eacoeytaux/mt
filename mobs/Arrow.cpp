#include "Arrow.hpp"

NAMESPACES
using mt::util::Arrow;

Arrow::Arrow(World* _world, const Coordinate & tip, const Vector & launch_speed) :
Object(_world, tip, 0, 0, 1, launch_speed) { }

void Arrow::update() {
    Object::add_velocity(GRAVITY * -0.5);
    Object::update();
    velocity(velocity() * 0.999); // TODO change to air resistance
}

void Arrow::draw(const Camera * _camera) const {
    Vector delta = velocity();
    delta.magnitude(24);
    Coordinate back_pos = position() - delta;
    _camera->draw_line(RED, Line(position(), back_pos));
}
