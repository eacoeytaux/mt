#include "Cloud.hpp"

#include "Random.hpp"
#include "World.hpp"

using namespace mt;

const float X_STRETCH = 2;
const int MIN_SMALL_PUFF_COUNT = 16;
const int MAX_SMALL_PUFF_COUNT = 24;
const int MIN_SMALL_PUFF_RADIUS = 8;
const int MAX_SMALL_PUFF_RADIUS = 20;
const float MAX_SMALL_PUFF_DISTANCE = 80;
const int MIN_LARGE_PUFF_COUNT = 16;
const int MAX_LARGE_PUFF_COUNT = 24;
const int MIN_LARGE_PUFF_RADIUS = 25;
const int MAX_LARGE_PUFF_RADIUS = 50;
const float MAX_LARGE_PUFF_DISTANCE = 60;
const float PUFF_OUTLINE_RATIO = 0.64;
const Color INSIDE_COLOR = Color(135, 206, 235);

Cloud::_puff::_puff(float _RADIUS, const Vector & _center_offset) {
    m_radius = _RADIUS;
    m_center_offset = _center_offset;
}

Cloud::Cloud(World* _world) : Object(_world, Coordinate()) {
    Object::width(max_dx());
    Object::height(max_dy());
    Object::z(0.1);
    
    Random::seed();
    
    // set location
    Coordinate location(-max_dx(), Random::r_float(max_dy()));
    m_center = location;
    
    int small_puff_count = Random::r_int(MIN_SMALL_PUFF_COUNT, MAX_SMALL_PUFF_COUNT);
    for_range (small_puff_count) {
        Vector offset(Random::r_Angle(), Random::r_float(MAX_SMALL_PUFF_DISTANCE));
        offset.dx(offset.dx() * X_STRETCH);
        m_puffs.push_back(_puff(Random::r_int(MIN_SMALL_PUFF_RADIUS, MAX_SMALL_PUFF_RADIUS), offset));
    }
    
    int large_puff_count = Random::r_int(MIN_LARGE_PUFF_COUNT, MAX_LARGE_PUFF_COUNT);
    for_range (large_puff_count) {
        Vector offset(Random::r_Angle(), Random::r_float(MAX_LARGE_PUFF_DISTANCE));
        offset.dx(offset.dx() * X_STRETCH);
        m_puffs.push_back(_puff(Random::r_int(MIN_LARGE_PUFF_RADIUS, MAX_LARGE_PUFF_RADIUS), offset));
    }
}

float Cloud::max_dx() const {
    return max((MAX_SMALL_PUFF_DISTANCE * X_STRETCH) + MAX_SMALL_PUFF_RADIUS, (MAX_LARGE_PUFF_DISTANCE * X_STRETCH) + MAX_LARGE_PUFF_RADIUS) * 2;
}

float Cloud::max_dy() const {
    return max(MAX_SMALL_PUFF_RADIUS + MAX_SMALL_PUFF_DISTANCE, MAX_LARGE_PUFF_RADIUS + MAX_LARGE_PUFF_DISTANCE) * 2;
}

void Cloud::update() {
    m_center += m_world->wind();
}

void Cloud::draw(const Camera & _camera) const {
    for_each (puff, m_puffs) {
        _camera.draw_circle(WHITE, Circle(puff.m_radius, m_center + puff.m_center_offset), FILLED_, m_z);
    }
    for_each (puff, m_puffs) {
        _camera.draw_circle(INSIDE_COLOR, Circle(puff.m_radius * PUFF_OUTLINE_RATIO, m_center + puff.m_center_offset), FILLED_, m_z);
    }
    
    Object::draw(_camera);
}
