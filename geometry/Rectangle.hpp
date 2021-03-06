#ifndef __Rectangle__
#define __Rectangle__

#include "Shape.hpp"

//#define Rectangles varray<Rectangle>

namespace mt {
namespace geometry {

class Triangle;
class Polygon;
class Circle;

class Rectangle : public Shape {
public:
    virtual ~Rectangle() { }
    Rectangle(float width = 0, float height = 0, const Coordinate & center = Coordinate(), const Angle & rotation = Angle());
    Rectangle(const Coordinate & farthest, const Coordinate & closest = Coordinate(), const Angle & rotation = Angle());
    
    Coordinate center() const;
    Rectangle & center(const Coordinate & center);
    float width() const;
    Rectangle & width(float);
    float height() const;
    Rectangle & height(float);
    Angle rotation() const;
    
    Shape & move(const Vector & vector) override;
    Shape & scale(float scale, const Coordinate & origin = Coordinate(0, 0)) override;
    Shape & rotate(const Angle & angle, const Coordinate & origin = Coordinate(0, 0)) override;
    Shape & mirror(const Vector & axis) override;
    
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
    float area() const override;
    uint sides() const override;
    
    bool contains(const Coordinate &) const;
    bool intersects(const Line &) const;
    Line intersection(const Line &) const;
    
    varray<Coordinate> coordinates() const override;
    varray<Line> lines() const override;
    varray<Triangle> triangles() const override;
    
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
}

#endif /* defined(__Rectangle__) */
