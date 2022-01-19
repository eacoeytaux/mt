#ifndef Shape_hpp
#define Shape_hpp

#include "Coordinate.hpp"
#include "Angle.hpp"
#include "Vector.hpp"
#include "Line.hpp"

namespace mt {
namespace geometry {

class Triangle;

class Shape {
public:
    virtual ~Shape() { }
    
    virtual float area() const = 0;
    virtual varray<Coordinate> coordinates() const = 0;
    virtual varray<Line> lines() const = 0;
    virtual varray<Triangle> triangles() const = 0;
    virtual uint sides() const { return (uint)coordinates().size(); };
    
    // virtual bool contains(const Coordinate &) const = 0; // TODO
    // virtual bool intersects(const Line &) const = 0; // TODO
    
    virtual Shape & move(const Vector &) = 0;
    virtual Shape & scale(float scale, const Coordinate & origin = Coordinate(0, 0)) = 0;
    virtual Shape & rotate(const Angle & angle, const Coordinate & origin = Coordinate(0, 0)) = 0;
    virtual Shape & mirror(const Vector & axis) = 0;
    Shape & mirror_x() { return mirror(Vector(1, 0)); }
    Shape & mirror_y() { return mirror(Vector(0, 1)); }
    
    bool operator!=(const Shape & _shape) const { return !(*this == _shape); }
    virtual bool operator==(const Shape & _shape) const {
        if (coordinates().size() != _shape.coordinates().size()) return false;
        for_range(coordinates().size()) if (coordinates()[i] != _shape.coordinates()[i]) return false;
        return true;
    }
};

}
}

#endif /* Shape_hpp */
