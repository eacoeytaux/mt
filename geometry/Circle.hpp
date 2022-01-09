#ifndef __Circle__
#define __Circle__

#include "Shape.hpp"

//#define Circles varray<Circle>

#define CIRCLE_PRECISION 32
#define CIRCLE_PRECISION_ANGLE ((2 * PI) / CIRCLE_PRECISION)

namespace mt {
namespace geometry {

class Triangle;

class Circle : public Shape {
public:
    Circle(float radius = 0, const Coordinate & center = Coordinate());
    
    Coordinate center() const;
    Circle & center(const Coordinate & center);
    float radius() const;
    Circle & radius(float radius);
    float diameter() const;
    Circle & diameter(float diameter);
    
    Shape & move(const Vector & vector) override;
    Shape & rotate_about(const Angle & angle, const Coordinate & origin = Coordinate(0, 0)) override;
    
    float lower_bound_x() const;
    float lower_bound_y() const;
    float upper_bound_x() const;
    float upper_bound_y() const;
    float area() const override;
    int sides() const override;
    
    bool contains(const Coordinate &) const;
    
    float x_high(float y) const;
    float x_low(float y) const;
    float y_high(float x) const;
    float y_low(float x) const;
    
//    bool intersects(const Line &) const;
//    Line intersection(const Line &) const;
    
    varray<Coordinate> coordinates() const override;
    varray<Line> lines() const override;
    varray<Line> arc(const Angle &, const Angle & = Angle(0)) const;
    varray<Triangle> triangles() const override;
    varray<Triangle> triangles(const unsigned int precision) const;
    
    float convert_to_radians(float distance) const;
    float convert_to_distance(float radians) const;
    
    Circle operator+(const Vector &) const;
    Circle & operator+=(const Vector &);
    Circle operator-(const Vector &) const;
    Circle & operator-=(const Vector &);
    
    bool operator==(const Circle &) const;
    bool operator!=(const Circle &) const;
    
private:
    float m_radius;
    Coordinate m_center;
};

}
}

#endif /* defined(__Circle__) */
