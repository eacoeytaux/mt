#include "World.hpp"

#include "Random.hpp"
#include "Player.hpp"

#include "Fire.hpp"
#include "Tree.hpp"

NAMESPACES
using mt::exists::World;

const float camera_zoom_ratio = 0.9;

World::World() :
m_sky(this) {
    m_objects = varray<shared_ptr<Object>>(0);
    reset();
}

void World::reset() {
    m_age = 0;
    
    m_objects.clear();
    m_camera.zoom(1);
    
    m_darkness = Darkness();
    
    m_wind = Vector(1.5, 0);
    m_sky = Sky(this, 200);
    
    for_each (terrain_edge, m_terrain.edges()) {
        int tree_count = Random::r_int(0, 2);
        for_range (tree_count) {
            Coordinate root = terrain_edge->vertex1()->position() + (Vector(terrain_edge->vertex1()->position(), terrain_edge->vertex2()->position()) * Random::r_float(1));
            m_objects.push_back(shared_ptr<Tree>(new Tree(this, root)));
        }
    }
    
    m_player = shared_ptr<Player>(new Player(this, Coordinate(120, 200)));
    m_objects.push_back(m_player);
    
    m_objects.push_back(shared_ptr<Fire>(new Fire(this, Coordinate(0, 30))));
}

void World::update() {
    ++m_age;
    
    // m_terrain.update();
    m_darkness.clear_light_sources();
    m_sky.update();
    
    for_each (object, m_objects) {
        object->update();
    }
    
    m_camera.update();
     
}

void World::draw() const {
    const Camera * camera = &m_camera;
    m_sky.draw(camera);
    m_terrain.draw(camera);
    for_each (object, m_objects) object->draw(camera);
    m_darkness.draw(camera);
    m_player->draw_reticle(camera); // draw reticle above everything else
#ifdef MT_DEBUG
    if (Debug::on) {
        float BARRIER_THICKNESS = 4 / m_camera.zoom();
        m_camera.draw_rectangle(RED, Rectangle(2 * (m_camera.width() + (BARRIER_THICKNESS / 2)), 2 * (m_camera.height() + (BARRIER_THICKNESS / 2)), Coordinate(0, 0)), BARRIER_THICKNESS + 1, 0);
    }
#endif
}

void World::mouse_movement(const Coordinate & screen_pos) {
    Coordinate world_pos = screen_pos - (Vector(m_camera.width(), m_camera.height()) / 2) + m_camera.center();
    Angle angle_from_player = Vector(m_player->position(), world_pos).angle();
    angle_from_player *= -1;
    m_player->aim(angle_from_player);
}

uint64_t World::age() const {
    return m_age;
}

shared_ptr<Player> World::player() {
    return m_player;
}

const Camera & World::camera() const {
    return m_camera;
}

void World::camera_target(const Coordinate & _target, bool hard_set) {
    if (hard_set) {
        m_camera.center(_target);
    } else {
        m_camera.target(_target);
    }
}

void World::camera_width(float _width) {
    m_camera.width(_width);
}

void World::camera_height(float _height) {
    m_camera.height(_height);
}

void World::camera_zoom_in() {
    m_camera.zoom(m_camera.zoom() / camera_zoom_ratio);
}

void World::camera_zoom_out() {
    m_camera.zoom(m_camera.zoom() * camera_zoom_ratio);
}

const Terrain & World::terrain() const {
    return m_terrain;
}

void World::lights(bool _lights) {
    if (_lights) {
        m_darkness.darkness_intensity(0);
    } else {
        m_darkness.darkness_intensity(1);
    }
}

Vector World::wind() const {
    return m_wind;
}

void World::wind(const Vector & _WIND) {
    m_wind = _WIND;
}

void World::add_light_source(const Coordinate & _position, const float _distance, const float _flicker) {
    m_darkness.add_light_source(_position, _distance, _flicker);
}
