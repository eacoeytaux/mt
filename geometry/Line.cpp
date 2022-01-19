#include "Line.hpp"

#include "mt.hpp"
#include "Vector.hpp"

NAMESPACES
using mt::geometry::Line;

Line::Line(const Coordinate & c1, const Coordinate & c2) {
    float x1 = c1.x();
    float y1 = c1.y();
    float x2 = c2.x();
    float y2 = c2.y();
    
    m_c1 = Coordinate(x1, y1);
    m_c2 = Coordinate(x2, y2);
    
    float x_high, y_high, x_low, y_low;
    
    if (float_le(x1, x2)) {
        x_low = x1;
        x_high = x2;
        if (float_eq(x1, x2) && float_gt(y1, y2)) { //if is vertical
            y_low = y2;
            y_high = y1;
        } else {
            y_low = y1;
            y_high = y2;
        }
    } else {
        x_low = x2;
        y_low = y2;
        x_high = x1;
        y_high = y1;
    }
    
    if (!float_eq(x_low, x_high)) {
        if (!float_eq(y_low, y_high)) {
            m_vertical = false;
            m_horizontal = false;
            float dx = (x2 - x1);
            float dy = (y2 - y1);
            m_m = dy / dx;
            m_b = y_low - (m_m * x_low);
        } else {
            m_vertical = false;
            m_horizontal = true;
            m_m = 0;
            m_b = y1;
        }
    } else {
        m_vertical = true;
        m_horizontal = false;
        m_m = 0;
        m_b = 0;
    }
}

Coordinate Line::c1() const {
    return m_c1;
}

void Line::c1(const Coordinate & c) {
    *this = Line(c, c2());
}

Coordinate Line::c2() const {
    return m_c2;
}

void Line::c2(const Coordinate & c) {
    *this = Line(c1(), c);
}

Angle Line::angle() const {
    return Vector(c1(), c2()).angle();
}

void Line::rotate(const Angle & a, const Coordinate & origin) {
    Vector v1(origin, c1());
    v1.rotate(a);
    c1(v1.destination());
    
    Vector v2(origin, c2());
    v2.rotate(a);
    c2(v2.destination());
}

void Line::mirror(const Vector & _axis) {
    c1(c1().mirror(_axis));
    c2(c2().mirror(_axis));
}

void Line::mirror_x() {
    mirror(Vector(1, 0));
}

void Line::mirror_y() {
    mirror(Vector(0, 1));
}

bool Line::vertical() const {
    return m_vertical;
}

bool Line::horizontal() const {
    return m_horizontal;
}

float Line::m() const {
    return m_m;
}

float Line::b() const {
    return m_b;
}

float Line::length() const {
    return c1().distance(c2());
}

float Line::x(float y) const {
    if (horizontal()) {
        
    } else if (vertical()) {
        if (in_range<float>(y, c1().y(), c2().y())) {
            return c1().x();
        }
    } else {
        float x = (y - m_b) / m_m;
        if (in_box(Coordinate(x, y))) {
            return x;
        }
    }
    
    return -0;
}

float Line::y(float x) const {
    if (vertical()) {
        
    } else if (horizontal()) {
        if (in_range<float>(x, c1().x(), c2().x())) {
            return c1().y();
        }
    } else {
        float y = (m_m * x) + m_b;
        if (in_box(Coordinate(x, y))) {
            return y;
        }
    }
    
    return -0;
}

Coordinate Line::right() const {
    if (c1().x() >= c2().x()) return c1();
    else return c2();
}

Coordinate Line::left() const {
    if (c1().x() <= c2().x()) return c1();
    else return c2();
}

Coordinate Line::high() const {
    if (c1().y() >= c2().y()) return c1();
    else return c2();
}

Coordinate Line::low() const {
    if (c1().y() <= c2().y()) return c1();
    else return c2();
}

bool Line::in_box(const Coordinate & c) const {
    return in_range<float>(c.x(), left().x(), right().x()) && in_range<float>(c.y(), low().y(), high().y());
}

bool Line::below(const Coordinate & c, bool inclusive) const {
    float x1 = c1().x();
    float y1 = c1().y();
    float x2 = c2().x();
    float y2 = c2().y();
    float eq = (((x2 - x1) * (c.y() - y1)) - ((y2 - y1) * (c.x() - x1)));
    if (inclusive && (eq == 0)) return true;
    else return (eq > 0);
}

bool Line::intersects(const Line & line) const {
    if (vertical() && line.vertical()) {
        return (c1().x() == line.c1().x());
    } else if (horizontal() && line.horizontal()) {
        return (c1().y() == line.c1().y()) ;
    } else if ((m_m == line.m_m) && (m_b == line.m_b)) {
        return true;
    }
    
    float x_intersect;
    float y_intersect;
    
    if (vertical()) {
        x_intersect = low().x();
        y_intersect = (line.horizontal() ? line.low().y() : (line.m_m * low().x()) + line.m_b);
    } else if (line.vertical()) {
        x_intersect = line.low().x();
        y_intersect = (horizontal() ? low().y() : (m_m * line.low().x()) + m_b);
    } else if (horizontal()) {
        x_intersect = (low().y() - line.m_b) / line.m_m;
        y_intersect = low().y();
    } else if (line.horizontal()) {
        x_intersect = (line.low().y() - m_b) / m_m;
        y_intersect = line.low().y();
    } else {
        x_intersect = (line.m_b - m_b) / (m_m - line.m_m);
        y_intersect = (m_m * x_intersect) + m_b;
    }
    
    Coordinate intersect(x_intersect, y_intersect);
    return (in_box(intersect) && line.in_box(intersect));
}

Coordinate Line::intersection(const Line & line) const {
    if (vertical() && line.vertical()) {
        if (float_eq(c1().x(), line.c1().x())) {
            return c1();
        }
    } else if (horizontal() && line.horizontal()) {
        if (c1().y() == line.c1().y()) {
            return c1();
        }
    } else if (float_eq(m_m, line.m_m) && float_eq(m_b, line.m_b)) {
        if (in_range(c1().x(), line.left().x(), line.right().x())) {
            return c1();
        }
        if (in_range(line.c1().x(), low().x(), high().x())) {
            return line.c1();
        }
    } else {
        float x_intersect;
        float y_intersect;
        
        if (vertical()) {
            x_intersect = low().x();
            y_intersect = (line.horizontal() ? line.low().y() : (line.m_m * low().x()) + line.m_b);
        } else if (line.vertical()) {
            x_intersect = line.low().x();
            y_intersect = (horizontal() ? low().y() : (m_m * line.low().x()) + m_b);
        } else if (horizontal()) {
            x_intersect = (low().y() - line.m_b) / line.m_m;
            y_intersect = low().y();
        } else if (line.horizontal()) {
            x_intersect = (line.low().y() - m_b) / m_m;
            y_intersect = line.low().y();
        } else {
            x_intersect = (line.m_b - m_b) / (m_m - line.m_m);
            y_intersect = (m_m * x_intersect) + m_b;
        }
        
        Coordinate intersect(x_intersect, y_intersect);
        if (in_box(intersect) && line.in_box(intersect)) {
            return intersect;
        }
    }
    
    return Coordinate(NEG_INFINITY, NEG_INFINITY);
}

bool Line::operator==(const Line & line) const {
    return ((high() == line.high()) && (low() == line.low())) || ((right() == line.right()) && (left() == line.left()));
}

bool Line::operator!=(const Line & line) const {
    return !(*this == line);
}

Line Line::operator+(const Vector & _v) const {
    return Line(c1() + _v, c2() + _v);
}

Line & Line::operator+=(const Vector & _v) {
    *this = Line(c1() + _v, c2() + _v);
    return *this;
}

Line Line::operator-(const Vector & _v) const {
    return Line(c1() - _v, c2() - _v);
}

Line & Line::operator-=(const Vector & _v) {
    *this = Line(c1() - _v, c2() - _v);
    return *this;
}
