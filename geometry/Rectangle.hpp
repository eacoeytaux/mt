#ifndef __Rectangle__
#define __Rectangle__

#include "Shape.hpp"

//#define Rectangles varray<Rectangle>

namespace mt {

class Triangle;
class Polygon;
class Circle;

class Rectangle : public Shape {
public:
    Rectangle(float width = 0, float height = 0, const Coordinate & center = Coordinate(), const Angle & rotation = Angle());
    Rectangle(const Coordinate & c1, const Coordinate & c2 = Coordinate(), const Angle & rotation = Angle());
    
    Coordinate center() const;
    void center(const Coordinate & center);
    float width() const;
    void width(float);
    float height() const;
    void height(float);
    Angle rotation() const;
    void rotate_to(const Angle &);
    void rotate(const Angle &);
    
    void move(const Vector & vector);
    void rotate_around_origin(const Angle &, const Coordinate & origin);
    
    Coordinate top_right() const;
    Coordinate top_left() const;
    Coordinate bottom_left() const;
    Coordinate bottom_right() const;
    Line top() const;
    Line left() const;
    Line bottom() const;
    Line right() const;
    float lower_bound_x() const;
    float lower_bound_y() const;
    float upper_bound_x() const;
    float upper_bound_y() const;
    float diagonal_length() const;
    float area() const;
    
    bool contains(const Coordinate &) const;
    bool intersects(const Line &) const;
    Line intersection(const Line &) const;
    bool intersects(const Rectangle &) const;
    bool intersects(const Circle &) const;
    
    varray<Coordinate> coordinates() const;
    Path lines() const;
    varray<Triangle> triangles() const;
    
    bool operator==(const Rectangle &) const;
    bool operator!=(const Rectangle &) const;
    
    struct RectangleSplit : public varray<Rectangle> {
    public:
        RectangleSplit();
        Rectangle top_right();
        Rectangle top_left();
        Rectangle bottom_left();
        Rectangle bottom_right();
    private:
        friend class Rectangle;
        RectangleSplit(const varray<Rectangle> &);
    };
    RectangleSplit split(const Coordinate & split_center) const;
    
    Rectangle operator+(const Vector &) const;
    Rectangle & operator+=(const Vector &);
    Rectangle operator-(const Vector &) const;
    Rectangle & operator-=(const Vector &);
    
private:
    Coordinate m_center;
    float m_width, m_height;
    Angle m_rotation;
};

}

#endif /* defined(__Rectangle__) */
