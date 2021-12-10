#ifndef Shape_hpp
#define Shape_hpp

#include "Coordinate.hpp"
#include "Angle.hpp"
#include "Vector.hpp"
#include "Line.hpp"

//#define Shapes varray<Shape>

namespace mt {

class Triangle;

class Shape {
public:
    virtual float area() const;
    virtual int sides() const;
    virtual varray<Coordinate> coordinates() const;
    virtual Path lines() const;
    virtual varray<Triangle> triangles() const;
    virtual void move(const Vector &);
    
    virtual bool operator==(const Shape &) const;
    virtual bool operator!=(const Shape &) const;
};

}

#endif /* Shape_hpp */
