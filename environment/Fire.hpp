#ifndef Fire_hpp
#define Fire_hpp

#include "mt.hpp"
#include "Object.hpp"
#include "Timer.hpp"

namespace mt {
namespace exst {

class Fire : public Object {
public:
    virtual ~Fire() { }
    Fire(World *, const Coordinate & center);
    
    void update(float dt = 1) override;
    void draw(const Camera *) const override;
    
    float visible_width() const override;
    float visible_height() const override;
    
private:
    struct Flame;
    struct Smoke;
    
    varray<Flame> m_flames_yellow;
    varray<Flame> m_flames_orange;
    varray<Smoke> m_smokes;
    Timer flame_timer;
    
    struct Flame {
    public:
        Flame(const float radius, const Coordinate & offset = Coordinate(0, 0));
        Coordinate offset;
        float radius;
    };
    
    struct Smoke {
    public:
        Smoke(const float radius, const Coordinate & offset = Coordinate(0, 0));
        Coordinate offset;
        float radius;
        bool alpha_growing = true;
        uint16_t alpha = 0;
    };
};

}
}

#endif /* Fire_hpp */
