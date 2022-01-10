#include "BackgroundTerrain.hpp"

NAMESPACES
using mt::util::BackgroundTerrain;

BackgroundTerrain::BackgroundTerrain(World * world, float _z) : Object(world, Coordinate(), 0, 0, _z) { }

void BackgroundTerrain::update(float _dt) {
    Object::update(_dt);
}

void BackgroundTerrain::draw(const Camera * _camera) const {
    Object::draw(_camera);
    _camera->draw_rectangle(GREEN, Rectangle(500, 500, Coordinate(0, 0)));
}
