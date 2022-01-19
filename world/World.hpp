#ifndef World_hpp
#define World_hpp

#include "mt.hpp"
#include "constants.hpp"
#include "geometry.hpp"
#include "graphics.hpp"
#include "physics.hpp"

#include "Camera.hpp"
#include "Darkness.hpp"
#include "Terrain.hpp"
#include "BackgroundTerrain.hpp"
#include "Sky.hpp"

#include "Player.hpp"

namespace mt {
namespace exst {

/// @class World
/// @brief everything that currently exists
class World {
public:
    virtual ~World();
    World();
    
    void clean_up();
    void reset();
    
    void update(float speed = 1);
    void draw() const;
    
    void mouse_movement(const Coordinate & screen_pos);
    
    uint64_t age() const;
    
    shared_ptr<Player> player();
    
    const Camera & camera() const;
    void camera_target(const Coordinate &, bool hard_set = false);
    void camera_width(const float);
    void camera_height(const float);
    void camera_zoom(const float zoom);
    void camera_zoom_in();
    void camera_zoom_out();
    
    const shared_ptr<Terrain> terrain() const;
    bool lights() const;
    void lights(bool);
    Vector wind() const;
    void wind(const Vector &);
    
    varray<shared_ptr<Object>> all_objects() const;
    varray<shared_ptr<Object>> objects_in_range(const Rectangle &) const;
    void add_object(shared_ptr<Object>);
    void add_projectile(shared_ptr<Object>);
    
    void add_light_source(const Coordinate & position, const float distance, const float flicker = 0);
    void add_light_source(const Coordinate & position, const float distance, const Color & tint, const float flicker = 0);
    
    Coordinate mouse_position() const;
    void mouse_position(const Coordinate & position);
    
private:
    void add_objects_from_queue();
protected:
    void add_object_from_queue(shared_ptr<Object>);
    void clear_objects();
    
private:
    void draw_cursor() const;
    
    uint64_t m_age = 0;
    mutable Camera m_camera;
    
    shared_ptr<Player> m_player = nullptr;
    varray<shared_ptr<Object>> m_object_queue;
    varray<shared_ptr<Object>> m_objects_all;
    varray<shared_ptr<Object>> m_objects_sorted_xy;
    mutable varray<shared_ptr<Object>> m_objects_sorted_z;
    varray<shared_ptr<Object>> m_projectiles;
    shared_ptr<Darkness> m_darkness;
    shared_ptr<Terrain> m_terrain;
    shared_ptr<BackgroundTerrain> m_background_terrain;
    Vector m_wind;
    Sky m_sky;
    
    Coordinate m_mouse_position;
};

}
}

#endif /* World_hpp */
