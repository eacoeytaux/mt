#ifndef Hook_hpp
#define Hook_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace exst {

/// @class Hook
class Hook : public Object {
public:
    virtual ~Hook() { }
    Hook(World * world, const Coordinate & hook_tip, const Coordinate & base, const Angle & angle = Angle());
    
    Angle angle() const;
    Hook & angle(const Angle &);
    Coordinate hook_tip() const;
    Coordinate hook_base() const;
    Coordinate base() const;
    Hook & base(const Coordinate &, const Angle &);
    float length() const;
    void length(float);
    float max_length() const;
    void max_length(float);
    
    Hook & fire(const Vector & launch_speed);
    Hook & retract();
    Hook & load();
    
    void update(float dt) override;
    void draw(const Camera * camera) const override;
    void draw_hook(const Camera * camera) const;
    void draw_rope(const Camera * camera) const;
    
private:
    Coordinate m_base;
    Angle m_angle;
    float m_length;
    float m_max_length;
    float m_growth_speed;
    float m_retract_speed = 16; // todo
    
    enum HOOK_STATE {
        LOADED,
        HOOKED,
        FIRING,
        RETRACTING
    } m_state = LOADED;
};

}
}

#endif /* Hook_hpp */
