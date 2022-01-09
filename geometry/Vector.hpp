#ifndef __Vector__
#define __Vector__

#include "mt.hpp"
#include "Coordinate.hpp"
#include "Angle.hpp"

namespace mt {
namespace geometry {

/// @class Vector
/// @brief distance and direction from coordinate that defaults as origin
class Vector {
public:
    /// @param dx delta x
    /// @param dy delta y
    /// @param origin vector start point, default (0,0)
    Vector(float dx = 0, float dy = 0, const Coordinate & origin = Coordinate(0, 0));
    /// @param angle angle of vector
    /// @param magnitude length of vector
    /// @param origin vector start point, default (0,0)
    Vector(Angle angle, float magnitude, const Coordinate & origin = Coordinate(0, 0));
    /// @param c1 start of vector
    /// @param c2 end of vector
    Vector(const Coordinate & c1, const Coordinate & c2);
    /// @param c end of vector, start is (0,0)
    Vector(const Coordinate & c);
    
    /// @return delta x
    float dx() const;
    /// @param dx new delta x
    Vector & dx(float dx);
    /// @return delta y
    float dy() const;
    /// @param dy new delta y
    Vector & dy(float dy);
    /// @param dx delta x
    /// @param dy delta y
    Vector & dxdy(float dx, float dy);
    /// @return origin of vector
    Coordinate origin() const;
    /// @param origin new origin of vector
    Vector & origin(const Coordinate & origin);
    /// @return destination of vector
    Coordinate destination() const;
    /// @param destination new destination of vector
    Vector & destination(const Coordinate destination);
    /// @return length of vector
    float magnitude() const;
    /// @param magnitude new length of vector
    Vector & magnitude(float magnitude);
    /// @brief sets new length of vector
    /// @param length new length of vector
    Vector & extend(float length);
    
    /// @return angle of vector
    Angle angle() const;
    /// @param angle angle to rotate to
    Vector & rotate_to_angle(const Angle & angle);
    /// @param rotation angle to rotate by
    Vector & rotate(const Angle & rotation);
    /// @brief mirrors across x axis
    Vector & mirror_horizontal();
    /// @brief mirrors across y axis
    Vector & mirror_vertical();
    
//    template<typename T>
//    void move(varray<T> & elements) const {
//        for_range (elements.size()) elements[i] += *this;
//    }
    
//    template<typename T>
//    varray<T> move(const varray<T> & elements) const {
//        varray<T> ret;
//        for_range (elements.size()) ret.push_back(elements[i]);
//        return ret;
//    }

    Vector operator+(const Vector &) const;
    Vector & operator+=(const Vector &);
    Vector operator-(const Vector &) const;
    Vector & operator-=(const Vector &);
    Vector operator*(float scale) const;
    Vector & operator*=(float scale);
    Vector operator/(float scale) const;
    Vector & operator/=(float scale);
    
    bool operator==(const Vector &) const;
    bool operator!=(const Vector &) const;
    
private:
    Coordinate m_origin;
    float m_dx, m_dy;
};

}
}

#endif /* defined(__Vector__) */
