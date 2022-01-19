#include "IcePick.hpp"

NAMESPACES
using mt::exst::IcePick;

const float HANDLE_LENGTH = 16;
const float HANDLE_THICKNESS = 5;
const float HEAD_OFFSET = 8;
const float HEAD_LENGTH = 18;
const Color HANDLE_COLOR = Color(198, 145, 70);
const Color METAL_COLOR = GRAY_MID;

IcePick::IcePick(World * _world, const Coordinate & _position) : Object(_world, Matter(_position)) { }

void IcePick::update() {
    Object::update();
}

void IcePick::draw(const Camera * _camera) const {
    Coordinate handle_base = position() + Vector(-10, -8);
    
    _camera->draw_line(HANDLE_COLOR, Line(handle_base, handle_base - Vector(0, HANDLE_LENGTH)), HANDLE_THICKNESS);
    
    Triangle head = Triangle({ handle_base - Vector(HEAD_OFFSET, HANDLE_LENGTH + HANDLE_THICKNESS * 1.5), handle_base - Vector(HEAD_OFFSET, HANDLE_LENGTH), handle_base - Vector(HEAD_OFFSET - HEAD_LENGTH, HANDLE_LENGTH) });
    _camera->draw_shape(METAL_COLOR, head);
}
