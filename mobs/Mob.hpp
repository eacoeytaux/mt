#ifndef Mob_hpp
#define Mob_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace exst {

/// @class Mob
/// @brief a living, moving object
class Mob : public Object {
public:
    virtual ~Mob() { }
    Mob(World * world, const Coordinate & center, const float width, const float height, uint health);
    
    virtual void update(float dt = 1);
    virtual void draw(const Camera *) const;
#ifdef MT_DEBUG
    virtual void draw_debug(const Camera *) const;
#endif
    
    /// @return whether mob is alive
    virtual bool alive() const;
    virtual void kill();
    
    /// @return mob's current health
    virtual uint health() const;
    /// @param health mob's new health
    virtual void health(uint health); // will increase max health if necessary
    /// @param percentage sets new health to percentage of maximum health
    virtual void health(float percentage);

    /// @param health amount to heal by
    virtual void heal(uint health);
    virtual void heal_full();
    /// @param health amount of health lost
    virtual void hurt(uint health);
    
    /// @return mob's maximum health
    virtual uint max_health() const;
    /// @param health new maximum health
    virtual void max_health(uint health); // will decrease health if necessary
    
protected:
    /// @brief make any altercations to velocity
    virtual void adjust_velocity(float dt);
    /// @brief move object thro dugh world
    virtual void move(float dt);
    
protected:
    mutable Timer m_blink_counter;
    
private:
    bool m_alive = true;
    Slider<uint> m_health;
};

}
}

#endif /* Mob_hpp */
