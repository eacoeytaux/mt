#ifndef Shape_hpp
#define Shape_hpp

#include "Coordinate.hpp"
#include "Angle.hpp"
#include "Vector.hpp"
#include "Line.hpp"

//#define Shapes varray<Shape>

namespace mt {
namespace geometry {

class Triangle;

class Shape {
public:
    virtual float area() const = 0;
    virtual int sides() const = 0;
    virtual varray<Coordinate> coordinates() const = 0;
    virtual varray<Line> lines() const = 0;
    virtual varray<Triangle> triangles() const = 0;
    virtual Shape & move(const Vector &) = 0;
    virtual Shape & rotate_about(const Angle & angle, const Coordinate & origin = Coordinate(0, 0)) = 0;
    
    virtual bool operator==(const Shape &) const;
    virtual bool operator!=(const Shape &) const;
};

}
}

#endif /* Shape_hpp */
