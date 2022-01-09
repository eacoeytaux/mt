#ifndef Object_hpp
#define Object_hpp

#include "mt.hpp"
#include "Constants.hpp"
#include "Geometry.hpp"
#include "Graphics.hpp"
#include "Physics.hpp"

namespace mt {
namespace exst {

class World;
class Object;
class TerrainEdge;

/// @class Object
/// @brief object that exists in world, super descriptive I know
class Object : public Mass, public Visible {
public:
    Object(World *, const Coordinate & position, const float width = 0, const float height = 0, const float z = 1, const Vector & velocity = Vector(0, 0));
    
    virtual void update(float dt = 1);
    virtual void draw(const Camera *) const;
    virtual void draw_shadow(const Camera *) const;
    
    float width() const;
    void width(const float);
    float height() const;
    void height(const float);
    float z() const;
    void z(const float);
    
    float gravity_ratio() const;
    void gravity_ratio(float);
    bool terrarin_boundaries() const;
    void terrarin_boundaries(bool);
    
    virtual Rectangle visable_box() const;
#ifdef MT_DEBUG
    virtual void draw_visable_box(const Camera *) const;
#endif
    
private:
    /// @brief handles all movement updates
    virtual void update_move(float dt);
    
protected:
    /// @brief make any altercations to velocity
    virtual void adjust_velocity(float dt);
    /// @brief move object through world
    virtual void move(float dt);
    /// @brief restitance ratio \(0, 1]
    virtual float resistance() const;
    
    /// @brief world object exists in
    World* m_world;
    
    /// @brief width of object
    float m_width;
    /// @brief height of object
    float m_height;
    /// @brief z value in world, which corresponds to parallax perspective (1 is playable plane)
    float m_z;
    
    float m_gravity_ratio = 1;
    
    /// @brief set to true for objects that cannot pass through terrarin
    bool m_terrarin_boundaries;
    /// @brief set to false for background objects and vampires
    bool m_casts_shadow;
    
    /// @brief terrain object is sitting on if any
    shared_ptr<TerrainEdge> m_ground = nullptr;
};

}
}

#endif /* Object_hpp */
