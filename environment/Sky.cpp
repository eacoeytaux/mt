#include "Sky.hpp"

#include "Random.hpp"

NAMESPACES
using mt::exst::Sky;

Sky::Sky(World * _world, int _cloud_regen_rate) : Object(_world, Matter(Coordinate(0, 0)), 0) {
    m_clouds = varray<shared_ptr<Cloud>>();
    m_cloud_regen_rate = _cloud_regen_rate;
    
    if (_cloud_regen_rate) {
        m_cloud_timer.reset(Random::r_int(m_cloud_regen_rate));
    }
    
    m_top_color = BLUE;
    m_bottom_color = Color(255, 140, 0);
}

void Sky::update(float dt) {
    if (m_cloud_timer.tick()) {
        m_cloud_timer.reset(m_cloud_regen_rate);
//        m_clouds.push_back(shared_ptr<Cloud>(new Cloud(m_world)));
    }
    
    for_each (cloud, m_clouds) cloud->update(dt);
}

void Sky::draw(const Camera * _camera) const {
    _camera->draw_shape({ m_top_color, m_top_color, m_bottom_color, m_bottom_color }, Rectangle(_camera->width() + 2, _camera->height() + 1, Coordinate(0, 0)), 0, 0); // added + 1 just in case
    
    for_each (cloud, m_clouds) {
        cloud->draw(_camera);
    }
}
