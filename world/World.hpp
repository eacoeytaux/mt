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
#include "Sky.hpp"

#include "Player.hpp"

namespace mt {
namespace exists {

/// @class World
/// @brief everything that currently exists
class World {
public:
    World();
    
    void reset();
    
    void update();
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
    
    const Terrain & terrain() const;
    bool lights() const;
    void lights(bool);
    Vector wind() const;
    void wind(const Vector &);
    
    void add_light_source(const Coordinate & position, const float distance, const float flicker = 0);
    
private:
    uint64_t m_age = 0;
    
    shared_ptr<Player> m_player = nullptr;
    
    Camera m_camera;
    varray<shared_ptr<Object>> m_objects;
    Darkness m_darkness;
    Terrain m_terrain;
    Vector m_wind;
    Sky m_sky;
};

}
}

#endif /* World_hpp */
