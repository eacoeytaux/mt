#include "Fire.hpp"

#include "Random.hpp"
#include "World.hpp"

NAMESPACES
using mt::exst::Fire;

const int LIGHT_DISTANCE = 4 * METER;
const int FLAME_WAIT = 5;
const Angle FLAME_DEVIATION = Angle(PI / 4);
const int FLAME_ORANGE_SPEED = 5;
const int FLAME_ORANGE_RADIUS = 2 * METER;
const float FLAME_ORANGE_SHRINK_RATE = 1.5;
const int FLAME_YELLOW_SPEED = 4;
const int FLAME_YELLOW_RADIUS = FLAME_ORANGE_RADIUS / 3 * 2;
const float FLAME_YELLOW_SHRINK_RATE = 1.5;
const float FLAME_WIND_RESISTANCE = 2;
const Angle SMOKE_DEVIATION = Angle(PI / 4);
const int SMOKE_SPEED = 4;
const float SMOKE_GROW_RATE = 1;
const float SMOKE_WIND_RESISTANCE = 1;
const int SMOKE_ALPHA = 80;
const int SMOKE_ALPHA_SHRINK_RATE = 1;
const Color FLAME_ORANGE_COLOR = Color(255, 127, 0, 216);
const Color FLAME_YELLOW_COLOR = Color(255, 196, 0, 172);
const uint8_t SMOKE_GRAY_VALUE = 127;

Fire::Flame::Flame(const Coordinate & _offset, const float _radius) {
    offset = _offset;
    radius = _radius;
}

Fire::Smoke::Smoke(const Coordinate & _offset, const float _radius, const uint16_t _alpha) {
    offset = _offset;
    radius = _radius;
    alpha = _alpha;
}

Fire::Fire(World* _world, const Coordinate & _center) : Object(_world, _center) {
    flame_timer.reset(FLAME_WAIT);
}

void Fire::update(float dt) {
    m_world->add_light_source(position() + Vector(0, METER), LIGHT_DISTANCE);
    
    Random::seed();
    
    if (flame_timer.tick()) {
        flame_timer.reset(FLAME_WAIT);
        m_flames_orange.push_back(Flame(position(), FLAME_ORANGE_RADIUS));
        m_flames_yellow.push_back(Flame(position(), FLAME_YELLOW_RADIUS));
    }
    
    for_each (& flame, m_flames_orange) {
        flame.radius -= FLAME_ORANGE_SHRINK_RATE;
        flame.offset += Vector(Angle((PI / 2) + Random::r_float(-FLAME_DEVIATION.radians(), FLAME_DEVIATION.radians())), FLAME_YELLOW_SPEED) + (m_world->wind() / FLAME_WIND_RESISTANCE);
    }
    while (m_flames_orange.size() && m_flames_orange[0].radius <= 0) {
        m_smokes.push_back(Smoke(position() + m_flames_orange[0].offset, 1, SMOKE_ALPHA));
        m_flames_orange.erase(m_flames_orange.begin());
    }
    
    for_each (& flame, m_flames_yellow) {
        flame.radius -= FLAME_YELLOW_SHRINK_RATE;
        flame.offset += Vector(Angle((PI / 2) + Random::r_float(-FLAME_DEVIATION.radians(), FLAME_DEVIATION.radians())), FLAME_ORANGE_SPEED) + (m_world->wind() / FLAME_WIND_RESISTANCE);
    }
    while (m_flames_yellow.size() && m_flames_yellow[0].radius <= 0) {
        m_flames_yellow.erase(m_flames_yellow.begin());
    }
    
    for_each (& smoke, m_smokes) {
        smoke.radius += SMOKE_GROW_RATE;
        smoke.alpha -= SMOKE_ALPHA_SHRINK_RATE;
        smoke.offset += Vector(Angle((PI / 2) + Random::r_float(-SMOKE_DEVIATION.radians(), SMOKE_DEVIATION.radians())), SMOKE_SPEED) + (m_world->wind() / SMOKE_WIND_RESISTANCE);
    }
    while (m_smokes.size() && m_smokes[0].alpha <= 0) {
        m_smokes.erase(m_smokes.begin());
    }
}

void Fire::draw(const Camera * _camera) const {
    for_each (flame, m_flames_orange) {
        _camera->draw_polygon(FLAME_ORANGE_COLOR, Polygon(4, flame.radius / 2, position() + flame.offset));
    }
    for_each (flame, m_flames_yellow) {
        _camera->draw_polygon(FLAME_YELLOW_COLOR, Polygon(4, flame.radius / 2, position() + flame.offset));
    }
    for_each (smoke, m_smokes) {
        _camera->draw_circle(Color(SMOKE_GRAY_VALUE, SMOKE_GRAY_VALUE, SMOKE_GRAY_VALUE, smoke.alpha), Circle(smoke.radius, position() + smoke.offset));
    }
}
