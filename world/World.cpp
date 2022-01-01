#include "World.hpp"

#include "Random.hpp"
#include "Player.hpp"

#include "Fire.hpp"
#include "Tree.hpp"

NAMESPACES
using mt::exst::World;

/// @brief how many updates world will run before it is shown
const int START_AGE = 512;
/// @brief how much the camera zooms in/out
const float CAMERA_ZOOM_RATIO = 0.9;

World::World() :
m_sky(this),
m_terrain(this) {
    m_objects = varray<shared_ptr<Object>>(0);
    reset();
}

void World::reset() {
    m_age = 0;
    
    clear_objects();
    m_camera.zoom(1);
    
    m_darkness = Darkness();
    
    m_wind = Vector(-1.5, 0);
    m_sky = Sky(this, 200);
    
    m_objects.push_back(shared_ptr<Object>(&m_terrain));
    
    for_each (terrain_edge, m_terrain.edges()) {
        int tree_count = Random::r_int(0, 2);
        for_range (tree_count) {
            Coordinate root = terrain_edge->vertex1()->position() + (Vector(terrain_edge->vertex1()->position(), terrain_edge->vertex2()->position()) * Random::r_float(1));
            add_object(shared_ptr<Tree>(new Tree(this, root)));
        }
    }
    
    m_player = shared_ptr<Player>(new Player(this, Coordinate(120, 200)));
    add_object(m_player);
    
    add_object(shared_ptr<Fire>(new Fire(this, Coordinate(0, 30))));
    
    for_range(START_AGE) update();
}

void World::update() {
    ++m_age;
    
    // sort object list
    struct object_less_than {
        // sort in order of z (includes layers), then x, then y
        inline bool operator() (const shared_ptr<Object> & obj1, const shared_ptr<Object> & obj2) {
            if (obj1->z() != obj2->z()) {
                return (obj1->z() < obj2->z());
            } else {
                if (obj1->layer_position() != obj2->layer_position()) return (obj1->layer_position() < obj2->layer_position());
            }
            if (obj1->position().x() != obj2->position().x()) return (obj1->position().x() < obj2->position().x());
            if (obj1->position().y() != obj2->position().y()) return (obj1->position().y() < obj2->position().y());
            return false;
        }
    };
    
    sort(m_objects.begin(), m_objects.end(), object_less_than());
    
    // m_terrain.update();
    m_darkness.clear_light_sources();
    m_sky.update();
    
    for_each (object, m_objects) {
        object->update();
    }
    
    for_each (object, m_object_queue) m_objects.push_back(object);
    m_object_queue.clear();
    
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
    m_camera.zoom(m_camera.zoom() / CAMERA_ZOOM_RATIO);
}

void World::camera_zoom_out() {
    m_camera.zoom(m_camera.zoom() * CAMERA_ZOOM_RATIO);
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

void World::clear_objects() {
    m_objects.clear();
    m_object_queue.clear();
}

void World::add_object(shared_ptr<Object> _object) {
    m_object_queue.push_back(_object);
}

void World::add_light_source(const Coordinate & _position, const float _distance, const float _flicker) {
    m_darkness.add_light_source(_position, _distance, _flicker);
}
