#ifndef Fire_hpp
#define Fire_hpp

#include "mt.hpp"
#include "Object.hpp"
#include "Timer.hpp"

namespace mt {
namespace exst {

class Fire : public Object {
public:
    Fire(World*, const Coordinate & center);
    
    void update(float dt = 1);
    void draw(const Camera *) const;
    
private:
    struct Flame;
    struct Smoke;
    
    varray<Flame> m_flames_yellow;
    varray<Flame> m_flames_orange;
    varray<Smoke> m_smokes;
    Timer flame_timer;
    
    struct Flame {
    public:
        Flame(const Coordinate & offset, const float radius);
        Coordinate offset;
        float radius;
    };
    
    struct Smoke {
    public:
        Smoke(const Coordinate & offset, const float radius, const uint16_t alpha);
        Coordinate offset;
        float radius;
        uint16_t alpha;
    };
};

}
}

#endif /* Fire_hpp */
