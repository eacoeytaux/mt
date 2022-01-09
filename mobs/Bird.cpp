#include "Bird.hpp"

NAMESPACES
using mt::exst::Feather;
using mt::exst::Bird;

const float FEATHER_LENGTH = 15;
const float FEATHER_BASE_LENGTH = 5;
const float FEATHER_STEM_LENGTH = 3;
const float FEATHER_STEM_THICKNESS = 2;

Feather::Feather(World * _world, const Coordinate & _position) : Object(_world, _position) {
    m_color = Random::r_Color();
    gravity_ratio(0.05);
}

void Feather::draw(const Camera * _camera) const {
    Coordinate center = position();
    Polygon feather = Polygon(varray<Coordinate>({ center + Vector(FEATHER_LENGTH, 0), center + Vector(0, -FEATHER_BASE_LENGTH), center + Vector(-FEATHER_BASE_LENGTH, 0), center + Vector(0, FEATHER_BASE_LENGTH) }));
    Line stem = Line(position(), position() - Vector(FEATHER_BASE_LENGTH + FEATHER_STEM_LENGTH));
    _camera->draw_polygon(m_color, feather);
    _camera->draw_line(m_color, stem, FEATHER_STEM_THICKNESS);
}

Bird::Bird(World * _world, const Coordinate & _position) : Object(_world, _position) { }
