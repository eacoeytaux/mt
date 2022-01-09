#ifndef World_hpp
#define World_hpp

#include "mt.hpp"
#include "Constants.hpp"
#include "Geometry.hpp"
#include "Graphics.hpp"
#include "Physics.hpp"

#include "Camera.hpp"
#include "Object.hpp"
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
    World();
    
    void reset();
    
    void update(float dt = 1);
    void draw() const;
    
    void mouse_movement(const Coordinate & screen_pos);
    
    uint64_t age() const;
    
    shared_ptr<Player> player();
    
    const Camera & camera() const;
    void camera_target(const Coordinate &, bool hard_set = false);
    void camera_width(const float);
    void camera_height(const float);
    void camera_zoom_in();
    void camera_zoom_out();
    
    const shared_ptr<Terrain> terrain() const;
    bool lights() const;
    void lights(bool);
    Vector wind() const;
    void wind(const Vector &);
    
    void add_object(shared_ptr<Object>);
    
    void add_light_source(const Coordinate & position, const float distance, const float flicker = 0);
    
protected:
    void clear_objects();
    
private:
    uint64_t m_age = 0;
    
    shared_ptr<Player> m_player = nullptr;
    
    Camera m_camera;
    varray<shared_ptr<Object>> m_objects;
    varray<shared_ptr<Object>> m_object_queue;
    shared_ptr<Darkness> m_darkness;
    shared_ptr<Terrain> m_terrain;
    shared_ptr<BackgroundTerrain> m_background_terrain;
    Vector m_wind;
    Sky m_sky;
};

}
}

#endif /* World_hpp */
