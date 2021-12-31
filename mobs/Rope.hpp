#ifndef Rope_hpp
#define Rope_hpp

#include "mt.hpp"
#include "Object.hpp"

namespace mt {
namespace exists {

class Rope : public Object {
public:
    Rope(World*, const Coordinate & center, float max_length, float growth_SPEED, float retract_SPEED);
    
    bool firing() const;
    void firing(bool);
    Angle angle() const;
    void angle(const Angle &);
    float length() const;
    void length(float);
    float max_length() const;
    void max_length(float);
    
    void update();
    void draw(const Camera *) const;
    
private:
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
