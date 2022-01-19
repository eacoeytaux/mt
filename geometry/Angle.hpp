#ifndef __Angle__
#define __Angle__

#include "mt.hpp"
#include "Coordinate.hpp"

//#define Angles varray<Angle>

namespace mt {
namespace geometry {

const float PI = 3.141592653589793238463;
const float RIGHT_ANGLE = (PI / 2);

/// @class Angle
/// @brief cartesian coordinate angle
class Angle {
public:
    virtual ~Angle() { }
    /// @param radians radians
    /// @param truncate whether or not radians in confined to [0, 2*pi)
    Angle(const float radians = 0, const bool truncate = true);
    /// @param dx delta x
    /// @param dy delta y
    /// @param truncate whether or not radians in confined to [0, 2*pi)
    Angle(const float dx, const float dy, const bool truncate = true);
    
    /// @return whether or not angle is truncating radians
    bool truncating() const;
    /// @param truncate whether or not angle should truncate radians
    Angle & truncate(const bool truncate);
    
    /// @return angle in radians
    float radians() const;
    /// @return angle in degrees
    float degrees() const;
    /// @param radians new radian value
    Angle & radians(const float radians);
    /// @param dx new delta x
    /// @param dy new delta y
    Angle & radians(const float dx, const float dy);
    /// @brief sin value of angle
    /// @param multiplier multiply sin value by this
    float sin(const float multiplier = 1.0) const;
    /// @brief cos value of angle
    /// @param multiplier multiply cos value by this
    float cos(const float multiplier = 1.0) const;
    
    /// @brief quadrant destination of vector lands in, if any
    QUADRANT quadrant() const;
    /// @brief axis destination of vector lands on, if any
    AXIS axis() const;
    /// @brief whether destination is in quadrant
    /// @param quadrant quadrant to check
    bool in_quadrant(QUADRANT quadrant) const;
    /// @brief whether destination is on axis
    /// @param axis axis to check
    bool on_axis(AXIS axis) const;
    
    Angle operator+(const Angle & angle) const;
    Angle & operator+=(const Angle & angle);
    Angle operator-(const Angle & angle) const;
    Angle & operator-=(const Angle & angle);
    
    Angle & operator=(float radians);
    Angle operator+(float radians) const;
    Angle & operator+=(float radians);
    Angle operator-(float radians) const;
    Angle & operator-=(float radians);
    Angle operator*(float scale) const;
    Angle & operator*=(float scale);
    Angle operator/(float scale) const;
    Angle & operator/=(float scale);
    
    bool operator==(const Angle & angle) const;
    bool operator!=(const Angle & angle) const;
    bool operator<(const Angle & angle) const;
    bool operator<=(const Angle & angle) const;
    bool operator>(const Angle & angle) const;
    bool operator>=(const Angle & angle) const;
    
    static float radians_to_degrees(const float radians);
    static float degrees_to_radians(const float degrees);
    
private:
    bool m_truncate; // keeps radians within [0, 2*pi)
    float m_radians;
#ifdef MT_DEBUG
    float m_degrees;
#endif
};

}
}

#endif /* defined(__Angle__) */
