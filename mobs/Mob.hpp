#ifndef Mob_hpp
#define Mob_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {

class Mob : public Object {
public:
    Mob(World*, const Coordinate & center, const float width, const float height);
    
    virtual void update();
    virtual void draw(const Camera &) const;
    
    virtual bool alive() const;
    virtual void kill();
    
    virtual int health() const;
    virtual void health(int health); // will increase max health if necessary
    virtual void health(float percentage);
    
    virtual void heal(int health);
    virtual void hurt(int health);
    
    virtual int max_health() const;
    virtual void max_health(int); // will decrease health if necessary
    
protected:
    Slider<int> m_health;
    
private:
    bool m_alive = true;
};

}

#endif /* Mob_hpp */
