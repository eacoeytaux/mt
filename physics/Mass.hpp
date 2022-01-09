#ifndef Mass_hpp
#define Mass_hpp

#include "mt.hpp"

#include "Geometry.hpp"

namespace mt {
namespace physics {

/// @class Mass
/// @brief anything that has volume
class Mass {
public:
    virtual ~Mass() { }
    Mass(const Coordinate & position = Coordinate(0, 0), const Vector & velocity = Vector(0, 0), const float mass = 0);
    
    float mass() const;
    Mass & mass(const float mass);
    Coordinate position() const;
    Mass & position(const Coordinate & position);
    Vector velocity() const;
    Mass & velocity(const Vector & velocity);
    Mass & add_velocity(const Vector & velocity);
    
private:
    float m_mass;
    Coordinate m_position;
    Vector m_velocity;
};

}
}

#endif /* Mass_hpp */
