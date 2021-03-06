#ifndef Polygon_hpp
#define Polygon_hpp

#include "Shape.hpp"

//#define Polygons varray<Polygon>

namespace mt {
namespace geometry {

class Triangle;
class Rectangle;
class Circle;

class Polygon : public Shape {
public:
    Polygon(const varray<Coordinate> & coordinates = { });
    Polygon(const varray<Vector> & coordinate_offsets, const Coordinate & center, Angle rotation = Angle(0));
    
    Polygon(const Circle &);
    Polygon(const Triangle &);
    Polygon(const Rectangle &);
    Polygon(int side_count, float radius, const Coordinate & center = Coordinate(0, 0), Angle rotation = Angle(0)); // creates equilateral
    
    Shape & move(const Vector & vector) override;
    Shape & scale(float scale, const Coordinate & origin = Coordinate(0, 0)) override;
    Shape & rotate(const Angle & angle, const Coordinate & origin = Coordinate(0, 0)) override;
    Shape & mirror(const Vector & axis) override;
    
    float area() const override;
    uint sides() const override;
    
    bool convex() const;
    
    float lower_bound_x() const;
    float lower_bound_y() const;
    float upper_bound_x() const;
    float upper_bound_y() const;
    
    varray<Coordinate> coordinates() const override;
    varray<Line> lines() const override;
    varray<Triangle> triangles() const override;
    
    Polygon operator+(const Vector &) const;
    Polygon & operator+=(const Vector &);
    Polygon operator-(const Vector &) const;
    Polygon & operator-=(const Vector &);
    
    bool operator==(const Polygon &) const;
    bool operator!=(const Polygon &) const;
    
private:
    Coordinate m_origin;
    varray<Coordinate> m_coordinates;
    bool m_convex;
    float m_lower_bound_x = 0;
    float m_lower_bound_y = 0;
    float m_upper_bound_x = 0;
    float m_upper_bound_y = 0;
    
    void split_into_convexes(const varray<Coordinate> & coordinates);
    varray<Polygon> m_splits;
};

}
}

#endif /* Polygon_hpp */
