#ifndef Object_hpp
#define Object_hpp

#include "mt.hpp"
#include "constants.hpp"
#include "geometry.hpp"
#include "graphics.hpp"
#include "Physics.hpp"

namespace mt {
namespace exst {

class World;
class Object;
class TerrainEdge;

/// @class Object
/// @brief object that exists in world, super descriptive I know
class Object : public Matter, public Visible {
public:
    virtual ~Object() { }
    Object(World *, const Matter & matter, const float z = 1);
    
    uint64_t id() const { return m_id; }
    
    void update_object(float dt = 1);
    void draw_object(const Camera *) const;
    
    virtual void update(float dt = 1);
    virtual void draw(const Camera *) const;
    
    virtual float width() const;
    virtual float height() const;
    virtual float z() const;
    virtual void z(const float);
    
    float gravity_ratio() const;
    void gravity_ratio(float);
    bool terrarin_boundaries() const;
    void terrarin_boundaries(bool);
    
    virtual Rectangle hit_box() const;
    virtual Rectangle visible_box() const;
    
#ifdef MT_DEBUG
    virtual void draw_debug(const Camera *) const;
    virtual void draw_hit_box(const Camera *) const;
    virtual void draw_visible_box(const Camera *) const;
#endif
    
    virtual bool operator==(const Object & other) const { return id() == other.id(); }
    virtual bool operator!=(const Object & other) const { return !(*this == other); }
    
private:
    /// @brief handles all movement updates
    virtual void update_move(float dt);
    
protected:
    /// @brief make any altercations to velocity
    virtual void adjust_velocity(float dt);
    /// @brief move object through world
    virtual void move(float dt);
    /// @brief restitance ratio \(0, 1]
    virtual float friction_resistance() const;
    
    /// @brief world object exists in
    World * m_world = nullptr; // TODO make private
    
private:
    const uint64_t m_id;
    
    float m_z = 1;
    
    /// @brief visual width of object
    float m_visible_width = 0;
    /// @brief visual height of object
    float m_visible_height = 0;
    
    virtual float visible_width() const;
    virtual float visible_height() const;
    void visible_width(const float);
    void visible_height(const float);
    
    float m_gravity_ratio = 1;
    
    /// @brief set to true for objects that cannot pass through terrarin
    bool m_terrarin_boundaries = true;
    
protected:
    /// @brief terrain object is sitting on if any
    shared_ptr<TerrainEdge> m_ground = nullptr;
};

}
}

#endif /* Object_hpp */
