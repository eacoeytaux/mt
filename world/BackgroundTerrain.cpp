#include "BackgroundTerrain.hpp"

NAMESPACES
using mt::exst::BackgroundTerrain;

BackgroundTerrain::BackgroundTerrain(World * world, float _z) : Object(world, Matter(Coordinate(0, 0), { Rectangle(1000, 1000) }), _z) { }

void BackgroundTerrain::update(float _dt) {
    Object::update(_dt);
}

void BackgroundTerrain::draw(const Camera * _camera) const {
    
    Object::draw(_camera);
    
    float min_x = -800;
    float max_x = 800;
    
    static bool set = false; // TODO
    static Polygon mountains;
    static varray<Coordinate> coors;
    if (!set) {
        set = true;
        coors.push_back(Coordinate(max_x, -500));
        
        Coordinate point = Coordinate(max_x, 500);
        coors.push_back(point);
        bool up = true;
        while (point.x() > min_x) {
            Angle angle_offset = PI / 2.5;
            if (up) angle_offset *= -1;
            up = !up;
            Vector offset(angle_offset, Random::r_float(400) + 200);
            offset.dx(offset.dx() * -1);
            point += offset;
            coors.push_back(point);
        }
//        coors.push_back(Coordinate(min_x, -500));
        
        mountains = Polygon(coors);
    }
    
//    _camera->draw_polygon(GRAY_MID, mountains, FILLED, z());
//    for_each (coordinate, coors) _camera->draw_shape(CYAN, Circle(5, coordinate), FILLED, z());
}
