#ifndef Object_hpp
#define Object_hpp

#include "mt.hpp"
#include "Constants.hpp"
#include "Geometry.hpp"
#include "Graphics.hpp"

#include "Visible.hpp"
#include "Terrain.hpp"

namespace mt {

class World;

class Object : public Visible {
public:
    Object(World*, const Coordinate & center, const float width = 0, const float height = 0, const float z = 1, const Vector & velocity = Vector(0, 0));
    
    virtual void update();
    virtual void draw(const Camera &) const;
    virtual void draw_shadow(const Camera &) const;
    
    Coordinate center() const;
    void center(const Coordinate &);
    float width() const;
    void width(const float);
    float height() const;
    void height(const float);
    float z() const;
    void z(const float);
    Vector velocity() const;
    void velocity(const Vector &);
    
    bool gravity_affected() const;
    void gravity_affected(bool);
    bool terrarin_boundaries() const;
    void terrarin_boundaries(bool);
    
    virtual Rectangle visable_box() const;
#ifdef MT_DEBUG
    virtual void draw_visable_box(const Camera &) const;
#endif
    
protected:
    virtual void update_velocity();
    virtual void move(const Vector &);
    
    World* m_world;
    
    Coordinate m_center;
    float m_width, m_height;
    float m_z;
    Vector m_velocity;
    
    bool m_gravity_affected; // set to true for objects that fall
    bool m_terrarin_boundaries; // set to true for objects that cannot pass through terrarin
    bool m_casts_shadow; // set to false for background objects and vampires
    
    shared_ptr<TerrainEdge> m_ground = nullptr;
};

}

#endif /* Object_hpp */
