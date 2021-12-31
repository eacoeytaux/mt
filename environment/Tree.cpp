#include "Tree.hpp"

#include "Random.hpp"
#include "World.hpp"

NAMESPACES
using mt::exists::Tree;

const Angle MAX_SWAY = PI / 32;
const float TRUNK_HEIGHT = 60;
const float TRUNK_THICKNESS = 20;
const float LEAVES_HEIGHT_BASE_LENGTH = 160;
const float LEAVES_SHRINK_RATIO = 0.64;

const Color TRUNK_COLOR = Color(165, 100, 6);
const Color LEAVES_COLOR = Color(0, 192, 0);

Tree::Tree(World* _world, const Coordinate & _root) : Object(_world, _root, 0, 0, 0.999) { }

void Tree::draw(const Camera * _camera) const {
    Random::seed(0); // TODO
    
    Coordinate base = position();
    Angle sway_angle = Angle(sin(m_world->age() / 40.0) * MAX_SWAY.radians());
    Vector trunk(Vector(base, base + Vector(sway_angle + (PI / 2), TRUNK_HEIGHT)));
    _camera->draw_line(TRUNK_COLOR, Line(trunk.origin(), trunk.destination()), TRUNK_THICKNESS);
    
    Coordinate top = trunk.destination();
    float shink_ratio = LEAVES_SHRINK_RATIO;
    for_range (4) {
        Vector sub_trunk(Vector(top, top + Vector((sway_angle * (i + 2)) + (PI / 2), 100.0 * shink_ratio)));
        // base leaves triangle
        Polygon leaves = Polygon(varray<Vector>({ Coordinate(0, 0), Coordinate(-LEAVES_HEIGHT_BASE_LENGTH * shink_ratio / 2, -LEAVES_HEIGHT_BASE_LENGTH * shink_ratio), Coordinate(LEAVES_HEIGHT_BASE_LENGTH * shink_ratio / 2, -LEAVES_HEIGHT_BASE_LENGTH * shink_ratio) }), sub_trunk.destination());
        leaves.rotate_around_origin(sway_angle * (i + 2), leaves.coordinates()[0]);
        _camera->draw_polygon(LEAVES_COLOR, leaves);
        
        top = sub_trunk.destination();
        shink_ratio *= LEAVES_SHRINK_RATIO;
    }
}
