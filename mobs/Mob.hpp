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
    Mob(World * world, const Coordinate & center, const float width, const float height);
    
    virtual void update();
    virtual void draw(const Camera *) const;
    
    /// @return whether mob is alive
    virtual bool alive() const;
    virtual void kill();
    
    /// @return mob's current health
    virtual int health() const;
    /// @param health mob's new health
    virtual void health(int health); // will increase max health if necessary
    /// @param percentage sets new health to percentage of maximum health
    virtual void health(float percentage);

    /// @param health amount to heal by
    virtual void heal(int health);
    virtual void heal_full();
    /// @param health amount of health lost
    virtual void hurt(int health);
    
    /// @return mob's maximum health
    virtual int max_health() const;
    /// @param health new maximum health
    virtual void max_health(int health); // will decrease health if necessary
    
private:
    bool m_alive = true;
    Slider<int> m_health;
};

}
}

#endif /* Mob_hpp */
