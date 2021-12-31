#ifndef Mass_hpp
#define Mass_hpp

#include "mt.hpp"

#include "Geometry.hpp"

namespace mt {
namespace physics {

/// @class Mass
/// @brief physically exists
class Mass {
public:
    virtual ~Mass() { }
    Mass(const Coordinate & position = Coordinate(0, 0), const float mass = 0);
    
    void move();
    
    float mass() const;
    void mass(const float mass);
    Coordinate position() const;
    void position(const Coordinate & position);
    Vector velocity() const;
    void velocity(const Vector & velocity);
    void add_velocity(const Vector & velocity);
    
private:
    float m_mass;
    Coordinate m_position;
    Vector m_velocity;
};

}
}

#endif /* Mass_hpp */
