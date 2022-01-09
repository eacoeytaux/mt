#ifndef Rope_hpp
#define Rope_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace exst {

class Rope : public Object {
public:
    Rope(World*, const Coordinate & center, float max_length, float growth_speed, float retract_speed);
    
    void update(float dt = 1) override;
    void draw(const Camera *) const override;
    
    Coordinate hook_position() const;
    
    bool firing() const;
    void firing(bool);
    Angle angle() const;
    void angle(const Angle &);
    float length() const;
    void length(float);
    float max_length() const;
    void max_length(float);
    
private:
    void adjust_velocity(float dt) override;
    void move(float dt) override;
    
    bool m_firing = false;
    Angle m_angle;
    float m_length;
    float m_max_length;
    float m_growth_speed;
    float m_retract_speed;
};

}
}

#endif /* Rope_hpp */
