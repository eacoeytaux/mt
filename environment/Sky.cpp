#include "Sky.hpp"

#include "Random.hpp"

NAMESPACES
using mt::exists::Sky;

Sky::Sky(World* _world, int _cloud_regen_rate) : Object(_world, Coordinate(0, 0)) {
    m_clouds = varray<shared_ptr<Cloud>>();
    m_cloud_regen_rate = _cloud_regen_rate;
    
    if (_cloud_regen_rate > 0) {
        Random::seed();
        m_cloud_timer.reset(Random::r_int(m_cloud_regen_rate));
        m_clouds.push_back(shared_ptr<Cloud>(new Cloud(_world)));
    }
}

void Sky::update() {
//    if (m_cloud_timer.tick()) {
//        Random::seed();
//        m_cloud_timer.reset(m_cloud_regen_rate);
//        m_clouds.push_back(shared_ptr<Cloud>(new Cloud(m_world)));
//    }
    
    for_each (cloud, m_clouds) {
        cloud->update();
    }
}

void Sky::draw(const Camera * _camera) const {
    _camera->draw_rectangle(BLUE, Rectangle(_camera->width() * 2, _camera->height() * 2, Coordinate(0, 0)), 0, 0); // TODO variablize the "* 2"?
    
    for_each (cloud, m_clouds) {
        cloud->draw(_camera);
    }
}
