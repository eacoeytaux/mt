#include "Bird.hpp"

#include "World.hpp"

NAMESPACES
using mt::exst::Feather;
using mt::exst::Bird;

const uint BIRD_HEALTH = 1;

const float FEATHER_LENGTH = 15;
const float FEATHER_BASE_LENGTH = 5;
const float FEATHER_STEM_LENGTH = 3;
const float FEATHER_STEM_THICKNESS = 2;

const float SPEED = 3;
const float ROTATIONAL_SPEED = 2;
const float ROTATIONAL_RADIUS = 160;
const float LIFT_SPEED = 1;
const float LIFT_DISTANCE = 16;

Feather::Feather(World * _world, const Coordinate & _position) : Object(_world, _position) {
    m_color = Random::r_Color();
    gravity_ratio(0.05);
}

void Feather::draw(const Camera * _camera) const {
    Coordinate center = position();
    Polygon feather = Polygon(varray<Coordinate>({ center + Vector(FEATHER_LENGTH, 0), center + Vector(0, -FEATHER_BASE_LENGTH), center + Vector(-FEATHER_BASE_LENGTH, 0), center + Vector(0, FEATHER_BASE_LENGTH) }));
    Line stem = Line(position(), position() - Vector(FEATHER_BASE_LENGTH + FEATHER_STEM_LENGTH));
    _camera->draw_shape(m_color, feather);
    _camera->draw_line(m_color, stem, FEATHER_STEM_THICKNESS);
}

Bird::Bird(World * _world, const Coordinate & _position) : Mob(_world, _position, 32, 32, BIRD_HEALTH) {
    gravity_ratio(0);
}

void Bird::kill() {
    gravity_ratio(1);
    Mob::kill();
}

void Bird::update(float dt) {
    if (alive() && m_world->player()) {
        Coordinate target = m_world->player()->position();
        target += Vector(0, 270);
        target += Vector(sin(m_world->age() * ROTATIONAL_SPEED / ROTATIONAL_RADIUS) * ROTATIONAL_RADIUS, 0);
        target += Vector(0, -sin((m_world->age() - (LIFT_DISTANCE / 2)) * LIFT_SPEED / LIFT_DISTANCE) * LIFT_DISTANCE);
        Vector movement = Vector(position(), target);
        if (movement.dx() > 0) movement.dx(min<float>(SPEED, movement.dx()));
        else movement.dx(max<float>(-SPEED, movement.dx()));
        velocity(movement);
    }
    
    Mob::update(dt);
}

void Bird::draw(const Camera * _camera) const {
    _camera->draw_line(RED, Line(position() + Vector(-16, 0), position() + Vector(16, 0)), 4);
    
    Polygon wing = Triangle({ Coordinate(0, 0), Coordinate(-24, sin(m_world->age() / 16.0) * 16.0), Coordinate(16, 0) });
    if (velocity().dx() < 0) wing.mirror_y();
    wing += position();
    _camera->draw_shape(RED, wing);
    
    Mob::draw(_camera);
}
