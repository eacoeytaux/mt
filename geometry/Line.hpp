#ifndef __Line__
#define __Line__

#include "mt.hpp"
#include "Coordinate.hpp"
#include "Angle.hpp"

namespace mt {

class Line {
public:
    Line(const Coordinate & c1, const Coordinate & c2);
    
    Coordinate c1() const;
    void c1(const Coordinate &);
    Coordinate c2() const;
    void c2(const Coordinate &);
    Angle angle() const;
    
    void rotate_around_origin(const Angle &, const Coordinate & = Coordinate(0, 0));
    
    bool vertical() const;
    bool horizontal() const;
    float length() const;
    float m() const;
    float b() const;
    
    float x(float y) const;
    float y(float x) const;
    
    Coordinate right() const;
    Coordinate left() const;
    Coordinate high() const;
    Coordinate low() const;
    
    bool in_box(const Coordinate &) const;
    bool below(const Coordinate &, bool inclusive = true) const;
    bool intersects(const Line &) const;
    Coordinate intersection(const Line &) const;
    
    bool operator==(const Line &) const;
    bool operator!=(const Line &) const;
    
    Line operator+(const Vector &) const;
    Line & operator+=(const Vector &);
    Line operator-(const Vector &) const;
    Line & operator-=(const Vector &);
    
private:
    Coordinate m_c1, m_c2;
    bool m_vertical, m_horizontal;
    float m_m, m_b;
};

typedef varray<Line> Path;

}

#endif /* defined(__Line__) */
