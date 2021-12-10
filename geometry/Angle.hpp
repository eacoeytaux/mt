#ifndef __Angle__
#define __Angle__

#include "mt.hpp"
#include "Coordinate.hpp"

//#define Angles varray<Angle>

namespace mt {

class Angle {
public:
    Angle(const float radians = 0, const bool truncate = true);
    Angle(const float dx, const float dy, const bool truncate = true);
    
    bool truncating() const;
    void truncate(const bool truncate);
    
    float radians() const;
    float degrees() const;
    void radians(const float radians);
    void radians(const float dx, const float dy);
    float sin(const float multiplier = 1.0) const;
    float cos(const float multiplier = 1.0) const;
    
    QUADRANT quadrant() const;
    AXIS axis() const;
    
    bool in_quadrant(QUADRANT) const;
    bool on_axis(AXIS) const;
    
    Angle operator+(const Angle &) const;
    Angle & operator+=(const Angle &);
    Angle operator-(const Angle &) const;
    Angle & operator-=(const Angle &);
    
    Angle & operator=(float radians);
    Angle operator+(float radians) const;
    Angle & operator+=(float radians);
    Angle operator-(float radians) const;
    Angle & operator-=(float radians);
    Angle operator*(float scale) const;
    Angle & operator*=(float scale);
    Angle operator/(float scale) const;
    Angle & operator/=(float scale);
    
    bool operator==(const Angle &) const;
    bool operator!=(const Angle &) const;
    bool operator <(const Angle &) const;
    bool operator <=(const Angle &) const;
    bool operator >(const Angle &) const;
    bool operator >=(const Angle &) const;
    
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

#endif /* defined(__Angle__) */
