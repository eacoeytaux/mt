#ifndef Matter_hpp
#define Matter_hpp

#include "mt.hpp"

#include "Geometry.hpp"

namespace mt {
namespace physics {

/// @class Matter
/// @brief anything that has volume
class Matter {
public:
    virtual ~Matter() { }
    Matter(const Coordinate & position, const Rectangle & space = Rectangle(0, 0), float mass = 0);
    
    float mass() const;
    Matter & mass(const float mass);
    Coordinate position() const;
    Matter & position(const Coordinate & position);
    Rectangle space() const;
    Matter & space(const Rectangle & space);
    Vector velocity() const;
    Matter & velocity(const Vector & velocity);
    Matter & add_velocity(const Vector & velocity);
    Matter & move(const Vector &);
    
private:
    float m_mass;
    Coordinate m_position;
    Rectangle m_space;
    Vector m_velocity;
};

}
}

#endif /* Matter_hpp */
