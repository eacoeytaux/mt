#ifndef Triangle_hpp
#define Triangle_hpp

#include "Shape.hpp"

//#define Triangles varray<Triangle>

namespace mt {

class Triangle : public Shape {
public:
    Triangle(const Coordinate & c1 = Coordinate(0, 0), const Coordinate & c2 = Coordinate(0, 0), const Coordinate & c3 = Coordinate(0, 0));
    Triangle(const Vector & offset1, const Vector & offset2, const Vector & offset3, const Coordinate & origin);

    Coordinate c1() const;
    Coordinate c2() const;
    Coordinate c3() const;
    
    Line line1() const;
    Line line2() const;
    Line line3() const;
    float area() const;
    
    varray<Coordinate> coordinates() const;
    Path lines() const;
    varray<Triangle> triangles() const;
    
    Triangle operator+(const Vector &) const;
    Triangle & operator+=(const Vector &);
    Triangle operator-(const Vector &) const;
    Triangle & operator-=(const Vector &);
    
    bool operator==(const Triangle &) const;
    bool operator!=(const Triangle &) const;
    
private:
    Coordinate m_c1, m_c2, m_c3;
};

}

#endif /* Triangle_hpp */
