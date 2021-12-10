#ifndef __Circle__
#define __Circle__

#include "Shape.hpp"

//#define Circles varray<Circle>

#define CIRCLE_PRECISION 32
#define CIRCLE_PRECISION_ANGLE ((2 * PI) / CIRCLE_PRECISION)

namespace mt {

class Triangle;

class Circle : public Shape {
public:
    Circle(float radius = 0, const Coordinate & center = Coordinate());
    
    Coordinate center() const;
    void center(const Coordinate &);
    float radius() const;
    void radius(float radius);
    float diameter() const;
    void diameter(float diameter);
    
    void move(const Vector & vector);
    
    float lower_bound_x() const;
    float lower_bound_y() const;
    float upper_bound_x() const;
    float upper_bound_y() const;
    float area() const;
    
    bool contains(const Coordinate &) const;
    
    float x_high(float y) const;
    float x_low(float y) const;
    float y_high(float x) const;
    float y_low(float x) const;
    // TODO add line
    
//    bool intersects(const Line &) const;
//    Line intersection(const Line &) const;

//    bool intersects(const Rectangle &) const;
//    bool intersects(const Circle &) const;
    
    varray<Coordinate> coordinates() const;
    Path lines() const;
    Path arc(const Angle &, const Angle & = Angle(0)) const;
    varray<Triangle> triangles() const;
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

#endif /* defined(__Circle__) */
