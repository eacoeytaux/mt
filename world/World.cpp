#include "World.hpp"

#include "Random.hpp"
#include "Player.hpp"

#include "Fire.hpp"
#include "Tree.hpp"
#include "Bird.hpp"

NAMESPACES
using mt::exst::World;

/// @brief how many updates world will run before it is shown
const int START_AGE = 512;
/// @brief how much the camera zooms in/out
const float CAMERA_ZOOM_RATIO = 0.95;

const float RETICLE_WIDTH = 1;
const float RETICLE_LENGTH = 9;

World::World() :
m_sky(this),
m_terrain(shared_ptr<Terrain>(new Terrain(this))) {
    m_objects_all = varray<shared_ptr<Object>>(0);
    m_objects_sorted_xy = varray<shared_ptr<Object>>(0);
    m_objects_sorted_z = varray<shared_ptr<Object>>(0);
    m_object_queue = varray<shared_ptr<Object>>(0);
    reset();
}

World::~World() {
    clean_up();
}

void World::clean_up() {
    clear_objects();
}

void World::reset() {
    clean_up();
    
    m_age = 0;
    m_camera.zoom(1);
    
    m_darkness = shared_ptr<Darkness>(new Darkness());
    
    m_wind = Vector(-1.5, 0);
//    m_sky = Sky(this, 200);
    
    m_background_terrain = shared_ptr<BackgroundTerrain>(new BackgroundTerrain(this, 0.75));
    
    m_terrain = shared_ptr<Terrain>(new Terrain(this));
    add_object(m_terrain);
    
    for_each (terrain_edge, m_terrain->edges()) {
        int tree_count = Random::r_int(0, 2);
        for_range (tree_count) {
//            Coordinate root = terrain_edge->vertex1()->position() + (Vector(terrain_edge->vertex1()->position(), terrain_edge->vertex2()->position()) * Random::r_float(1));
//            add_object(shared_ptr<Tree>(new Tree(this, root)));
        }
    }
    
    add_object(shared_ptr<Fire>(new Fire(this, Coordinate(0, 30))));
    
    add_object(shared_ptr<Bird>(new Bird(this, Coordinate(-100, 100))));
    
    for_range(START_AGE) update();
    
    m_player = shared_ptr<Player>(new Player(this, Coordinate(120, 200)));
    add_object(m_player);
}

void World::update(float dt) {
    ++m_age;
    
    // sort object list
    struct object_update_less_than {
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
    
    add_objects_from_queue();
    sort(m_objects_sorted_xy.begin(), m_objects_sorted_xy.end(), object_update_less_than());
    
    // m_terrain.update(float dt = 1);
    m_darkness->clear_light_sources();
    
    m_sky.update(dt);
    
    // update all objects
    for_each (object, m_objects_sorted_xy) object->update_object(dt);
    
    // delete marked objects
    // TODO
    
    Coordinate camera_center_pre = m_camera.center();
    if (m_player) camera_target(m_player->position());
    m_camera.update(dt); // must come after camera target is updated
    Coordinate camera_center_post = m_camera.center();
    Vector d_camera_center = camera_center_post - camera_center_pre;
    m_mouse_position += d_camera_center;
}

void World::clear_objects() {
    m_objects_all.clear();
    m_objects_sorted_xy.clear();
    m_objects_sorted_z.clear();
    m_object_queue.clear();
}

varray<shared_ptr<Object>> World::all_objects() const {
    return m_objects_all;
}

varray<shared_ptr<Object>> World::objects_in_range(const Rectangle & _rectangle) const {
    varray<shared_ptr<Object>> objects;
    
    for_each (object, m_objects_sorted_xy) {
        // TODO add hitbox width / height
        
        if (in_range<float>(object->position().x(), _rectangle.center().x() + (_rectangle.width() / 2), _rectangle.center().x() - (_rectangle.width() / 2))) { // check x
            if (in_range<float>(object->position().y(), _rectangle.center().y() + (_rectangle.height() / 2), _rectangle.center().y() - (_rectangle.height() / 2))) { // check y
                objects.push_back(object);
            }
        }
    }
    
    return objects;
}

void World::add_object(shared_ptr<Object> _object) {
    m_object_queue.push_back(_object);
}

void World::add_projectile(shared_ptr<Object> _object) {
    m_projectiles.push_back(_object);
    add_object(_object);
}

void World::add_objects_from_queue() {
    for_each (object, m_object_queue) {
        add_object_from_queue(object);
    }
    m_object_queue.clear();
}

void World::add_object_from_queue(shared_ptr<Object> _object) {
    m_objects_all.push_back(_object);
    m_objects_sorted_xy.push_back(_object);
    m_objects_sorted_z.push_back(_object);
}

void World::add_light_source(const Coordinate & _position, const float _distance, const float _flicker) {
    m_darkness->add_light_source(_position, _distance, _flicker);
}

void World::add_light_source(const Coordinate & _position, const float _distance, const Color & _tint, const float _flicker) {
    m_darkness->add_light_source(_position, _distance, _tint, _flicker);
}

void World::draw() const {
    const Camera * camera = &m_camera;
    
    // sort object list
    struct object_draw_less_than {
        // sort in order of z (includes layers), then x, then y
        inline bool operator() (const shared_ptr<Object> & obj1, const shared_ptr<Object> & obj2) {
            if (obj1->z() != obj2->z()) {
                return (obj1->z() < obj2->z());
            } else {
                if (obj1->layer_position() != obj2->layer_position()) return (obj1->layer_position() < obj2->layer_position());
            }
            return false;
        }
    };
    
    sort(m_objects_sorted_z.begin(), m_objects_sorted_z.end(), object_draw_less_than());
    
    m_sky.draw(camera);
    if (m_background_terrain) m_background_terrain->draw(camera);
    for_each (object, m_objects_sorted_z) object->draw_object(camera);
    m_darkness->draw(camera);
#ifdef MT_DEBUG
    if (Debug::on) {
        for_each (object, m_objects_sorted_z) object->draw_debug(camera);
        m_camera.debug_overlay();
    }
#endif
    draw_cursor();
    m_camera.render();
}
    
void World::draw_cursor() const {
     m_camera.draw_shape(BLACK, Rectangle((RETICLE_LENGTH + 2) / m_camera.zoom(), (RETICLE_WIDTH + 2) / m_camera.zoom(), m_mouse_position), 0);
     m_camera.draw_shape(BLACK, Rectangle((RETICLE_WIDTH + 2) / m_camera.zoom(), (RETICLE_LENGTH + 2) / m_camera.zoom(), m_mouse_position), 0);
     m_camera.draw_shape(WHITE, Rectangle(RETICLE_WIDTH / m_camera.zoom(), RETICLE_LENGTH / m_camera.zoom(), m_mouse_position), 0);
     m_camera.draw_shape(WHITE, Rectangle(RETICLE_LENGTH / m_camera.zoom(), RETICLE_WIDTH / m_camera.zoom(), m_mouse_position), 0);
}

void World::mouse_movement(const Coordinate & screen_pos) {
    Coordinate world_pos = m_camera.center() + screen_pos - ((Vector(m_camera.width(), m_camera.height()) / 2));
    world_pos.y(((world_pos.y() - m_camera.center().y()) * -1) + m_camera.center().y());
    Vector center_offset(m_camera.center(), world_pos);
    center_offset /= m_camera.zoom();
    world_pos = center_offset.destination();
    m_mouse_position = world_pos;
    
    if (m_player) {
        Angle angle_from_player = Vector(m_player->position(), m_mouse_position).angle();
        m_player->aim(angle_from_player);
    }
}

Coordinate World::mouse_position() const {
    return m_mouse_position;
}

void World::mouse_position(const Coordinate & _position) {
    m_mouse_position = _position;
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

void World::camera_zoom(const float _zoom) {
    m_camera.zoom(_zoom);
}

void World::camera_zoom_in() {
    m_camera.zoom(m_camera.zoom() / CAMERA_ZOOM_RATIO);
}

void World::camera_zoom_out() {
    m_camera.zoom(m_camera.zoom() * CAMERA_ZOOM_RATIO);
}

const shared_ptr<Terrain> World::terrain() const {
    return m_terrain;
}

void World::lights(bool _lights) {
    if (_lights) {
        m_darkness->darkness_intensity(0);
    } else {
        m_darkness->darkness_intensity(1);
    }
}

Vector World::wind() const {
    return m_wind;
}

void World::wind(const Vector & _WIND) {
    m_wind = _WIND;
}
