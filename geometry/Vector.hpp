#ifndef __Vector__
#define __Vector__

#include "mt.hpp"
#include "Coordinate.hpp"
#include "Angle.hpp"

namespace mt {

class Vector {
public:
    Vector(float dx = 0, float dy = 0, const Coordinate & origin = Coordinate(0, 0));
    Vector(Angle a, float magnitude, const Coordinate & origin = Coordinate(0, 0));
    Vector(const Coordinate & c1, const Coordinate & c2);
    Vector(const Coordinate & c);
    
    float dx() const;
    void dx(float dx);
    float dy() const;
    void dy(float dy);
    void dxdy(float dx, float dy);
    Coordinate origin() const;
    void origin(const Coordinate & origin);
    Coordinate destination() const;
    void destination(const Coordinate destination);
    float magnitude() const;
    void magnitude(float magnitude);
    void extend(float length);
    
    Angle angle() const;
    void rotate_to_angle(const Angle & angle);
    void rotate(const Angle & rotation);
    void mirror_horizontal();
    void mirror_vertical();
    
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

#endif /* defined(__Vector__) */
