#include "Rectangle.hpp"

#include "Triangle.hpp"
#include "Polygon.hpp"
#include "Circle.hpp"

using namespace mt;

Rectangle::Rectangle(const float _width, const float _height, const Coordinate & _center, const Angle & _rotation) {
    center(_center);
    width(_width);
    height(_height);
    rotate_to(_rotation);
}

Rectangle::Rectangle(const Coordinate & _c1, const Coordinate & _c2, const Angle & _rotation) {
    Coordinate c1 = _c1;
    Coordinate c2 = _c2;
    Vector v1 = Vector(c1);
    Vector v2 = Vector(c2);
    
    // line up with axes
    v1.rotate(_rotation * -1);
    v2.rotate(_rotation * -1);
    
    float width = abs<float>(v1.dx() - v2.dx());
    float height = abs<float>(v1.dy() - v2.dy());
    
    Vector center = (v1 + v2) / 2;
    center.rotate(_rotation);
    
    *this = Rectangle(width, height, center.destination(), _rotation);
}

Coordinate Rectangle::center() const {
    return m_center;
}

void Rectangle::center(const Coordinate & _center) {
    m_center = _center;
}

float Rectangle::width() const {
    return m_width;
}

void Rectangle::width(const float _width) {
    m_width = _width;
}

float Rectangle::height() const {
    return m_height;
}

void Rectangle::height(const float _height) {
    m_height = _height;
}

Angle Rectangle::rotation() const {
    return m_rotation;
}

void Rectangle::rotate_to(const Angle & _rotation) {
    m_rotation = _rotation;
}

void Rectangle::rotate(const Angle & _d_angle) {
    rotate_to(rotation() + _d_angle);
}

void Rectangle::move(const Vector & _v) {
    center(center() + _v);
}

void Rectangle::rotate_around_origin(const Angle & _d_angle, const Coordinate & _origin) {
    Vector v(_origin, center());
    v.rotate(_d_angle);
    center(v.destination());
    rotate_to(rotation() + _d_angle);
}

Coordinate Rectangle::top_right() const {
    Vector v(width() / 2, height() / 2);
    v.rotate(rotation());
    return center() + v;
}

Coordinate Rectangle::top_left() const {
    Vector v(-width() / 2, height() / 2);
    v.rotate(rotation());
    return center() + v;
}

Coordinate Rectangle::bottom_left() const {
    Vector v(-width() / 2, -height() / 2);
    v.rotate(rotation());
    return center() + v;
}

Coordinate Rectangle::bottom_right() const {
    Vector v(width() / 2, -height() / 2);
    v.rotate(rotation());
    return center() + v;
}

Line Rectangle::top() const {
    return Line(top_right(), top_left());
}

Line Rectangle::left() const {
    return Line(top_left(), bottom_left());
}

Line Rectangle::bottom() const {
    return Line(bottom_left(), bottom_right());
}

Line Rectangle::right() const {
    return Line(bottom_right(), top_right());
}

float Rectangle::lower_bound_x() const {
    return min<float>({ top_right().x(), bottom_right().x(), bottom_left().x(), top_left().x() });
}

float Rectangle::lower_bound_y() const {
    return min<float>({ top_right().y(), bottom_right().y(), bottom_left().y(), top_left().y() });
}

float Rectangle::upper_bound_x() const {
    return max<float>({ top_right().x(), bottom_right().x(), bottom_left().x(), top_left().x() });
}

float Rectangle::upper_bound_y() const {
    return max<float>({ top_right().y(), bottom_right().y(), bottom_left().y(), top_left().y() });
}

float Rectangle::diagonal_length() const {
    return top_left().distance(bottom_right());
}

float Rectangle::area() const {
    return width() * height();
}

bool Rectangle::contains(const Coordinate & _coordinate) const {
    bool top_below = top().below(_coordinate);
    bool right_below =  right().below(_coordinate);
    bool bottom_below = bottom().below(_coordinate);
    bool left_below = left().below(_coordinate);
    return top_below && right_below && bottom_below && left_below;
}

bool Rectangle::intersects(const Line & _line) const {
    return (contains(_line.c1()) || contains(_line.c2()) ||
            _line.intersects(top()) || _line.intersects(right()) ||
            _line.intersects(bottom()) || _line.intersects(left()));
}

Line Rectangle::intersection(const Line & _line) const {
    Coordinate c1 = _line.c1();
    Coordinate c2 = _line.c2();
    bool containsC1 = contains(c1);
    bool containsC2 = contains(c2);
    
    if (containsC1) {
        if (containsC2) return _line;
        
        if (_line.intersects(top())) {
            return Line(c1, _line.intersection(top()));
        } else if (_line.intersects(right())) {
            return Line(c1, _line.intersection(right()));
        } else if (_line.intersects(bottom())) {
            return Line(c1, _line.intersection(bottom()));
        } else if (_line.intersects(left())) {
            return Line(c1, _line.intersection(left()));
        }
    } else if (containsC2) {
        if (_line.intersects(top())) {
            return Line(_line.intersection(top()), c2);
        } else if (_line.intersects(right())) {
            return Line(_line.intersection(right()), c2);
        } else if (_line.intersects(bottom())) {
            return Line(_line.intersection(bottom()), c2);
        } else if (_line.intersects(left())) {
            return Line(_line.intersection(left()), c2);
        }
    } else {
        Coordinate i1, i2;
        bool found1 = false, found2 = false;
        if (_line.intersects(top())) {
            i1 = _line.intersection(top());
            found1 = true;
        } else if (_line.intersects(right())) {
            if (!found1) {
                i1 = _line.intersection(right());
                found1 = true;
            } else {
                i2 = _line.intersection(right());
                found2 = true;
            }
        } else if (_line.intersects(bottom())) {
            if (!found1) {
                i1 = _line.intersection(bottom());
                found1 = true;
            } else {
                i2 = _line.intersection(bottom());
                found2 = true;
            }
        } else if (_line.intersects(left())) {
            if (!found1) {
                i1 = _line.intersection(left());
                found1 = true;
            } else {
                i2 = _line.intersection(left());
                found2 = true;
            }
        }
        
        if (found1 && found2) {
            if (_line.c1().distance(i1) < _line.c1().distance(i2)) swap<Coordinate>(i1, i2);
            return Line(i1, i2);
        }
    }
    
    return Line(Coordinate(NEG_INFINITY, NEG_INFINITY), Coordinate(NEG_INFINITY, NEG_INFINITY));
}

bool Rectangle::intersects(const Rectangle & _rectangle) const {
    // TODO
    return false;
}

bool Rectangle::intersects(const Circle & _circle) const {
    // TODO
    return false;
}

varray<Coordinate> Rectangle::coordinates() const {
    return { top_right(), top_left(), bottom_left(), bottom_right() };
}

Path Rectangle::lines() const {
    return { top(), left(), bottom(), right() };
}

varray<Triangle> Rectangle::triangles() const {
    return { Triangle(top_right(), bottom_right(), top_left()), Triangle(bottom_left(), top_left(), bottom_right()) };
}

Rectangle::RectangleSplit::RectangleSplit() :
varray<Rectangle>(4, Rectangle(0, 0, COORDINATE_NEG_INFINITY)) { }

Rectangle::RectangleSplit::RectangleSplit(const varray<Rectangle> & _array) :
varray<Rectangle>(_array) {
    Assert::fatal(size() == 4, "RectangleSplit does not contain 4 Rectangles");
}

Rectangle Rectangle::RectangleSplit::top_right() {
    return (*this)[0];
}

Rectangle Rectangle::RectangleSplit::top_left() {
    return (*this)[1];
}

Rectangle Rectangle::RectangleSplit::bottom_left() {
    return (*this)[2];
}

Rectangle Rectangle::RectangleSplit::bottom_right() {
    return (*this)[3];
}

Rectangle::RectangleSplit Rectangle::split(const Coordinate & _split) const {
    const Rectangle NEG_RECTANGLE(0, 0, COORDINATE_NEG_INFINITY);

    bool top_below = top().below(_split);
    bool right_below =  right().below(_split);
    bool bottom_below = bottom().below(_split);
    bool left_below = left().below(_split);

    if (top_below && right_below && bottom_below && left_below) {
        Rectangle top_right_rectangle(_split, top_right());
        Rectangle bottom_right_rectangle(_split, bottom_right());
        Rectangle bottom_left_rectangle(_split, bottom_left());
        Rectangle top_left_rectangle(_split, top_left());
        return RectangleSplit({ top_right_rectangle, top_left_rectangle, bottom_left_rectangle, bottom_right_rectangle });
    }

    Vector center_adjusted_vector = Vector(center());
    Vector split_adjusted_vector = Vector(_split);
    center_adjusted_vector.rotate(rotation() * -1);
    split_adjusted_vector.rotate(rotation() * -1);
    Coordinate center_adjusted = center_adjusted_vector.destination();
    Coordinate split_adjusted = split_adjusted_vector.destination();

    if (top_below && bottom_below) {
        Vector intersection_left(Coordinate(center_adjusted.x() - (width() / 2), split_adjusted.y()));
        intersection_left.rotate(rotation());
        Rectangle top_rectangle(intersection_left.destination(), top_right());
        Rectangle bottom_rectangle(intersection_left.destination(), bottom_right());
        if (right_below) return RectangleSplit({ top_rectangle, NEG_RECTANGLE, NEG_RECTANGLE, bottom_rectangle });
        else if (left_below) return RectangleSplit({ NEG_RECTANGLE, top_rectangle, bottom_rectangle, NEG_RECTANGLE });
    }

    if (right_below && left_below) {
        Vector intersection_bottom(Coordinate(split_adjusted.x(), center_adjusted.y() - (height() / 2)));
        intersection_bottom.rotate(rotation());
        Rectangle left_rectangle(intersection_bottom.destination(), top_left());
        Rectangle right_rectangle(intersection_bottom.destination(), top_right());
        if (top_below) return RectangleSplit({ right_rectangle, left_rectangle, NEG_RECTANGLE, NEG_RECTANGLE });
        else if (bottom_below) return RectangleSplit({ NEG_RECTANGLE, NEG_RECTANGLE, left_rectangle, right_rectangle });
    }

    // no actual intersection
    if (top_below) {
        if (right_below) return RectangleSplit({ *this, NEG_RECTANGLE, NEG_RECTANGLE, NEG_RECTANGLE });
        if (left_below) return RectangleSplit({ NEG_RECTANGLE, *this, NEG_RECTANGLE, NEG_RECTANGLE });
    } else if (bottom_below) {
        if (left_below) return RectangleSplit({ NEG_RECTANGLE, NEG_RECTANGLE, *this, NEG_RECTANGLE });
        if (right_below) return RectangleSplit({ NEG_RECTANGLE, NEG_RECTANGLE, NEG_RECTANGLE, *this });
    }

    return RectangleSplit({ NEG_RECTANGLE, NEG_RECTANGLE, NEG_RECTANGLE, NEG_RECTANGLE });
}

Rectangle Rectangle::operator+(const Vector & _v) const {
    return Rectangle(width(), height(), center() + _v);
}

Rectangle & Rectangle::operator+=(const Vector & _v) {
    center(center() + _v);
    return *this;
}

Rectangle Rectangle::operator-(const Vector & _v) const {
    return *this + (_v * -1);
}

Rectangle & Rectangle::operator-=(const Vector & _v) {
    center(center() + (_v * -1));
    return *this;
}

bool Rectangle::operator==(const Rectangle & _rectangle) const {
    return (float_eq(width(), _rectangle.width()) && float_eq(height(), _rectangle.height()) && (center() == _rectangle.center()));
}

bool Rectangle::operator!=(const Rectangle & _rectangle) const {
    return !(*this == _rectangle);
}
