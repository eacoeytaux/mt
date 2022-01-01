#include "SysGraphics.hpp"

#define GL_SILENCE_DEPRECATION

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

NAMESPACES
using mt::graphics::SysGraphics;

void glColor(const Color & _color) {
    glColor4f(_color.r() / 255.f, _color.g() / 255.f, _color.b() / 255.f, _color.a() / 255.f);
}

GLint * glCoordinate(const Coordinate & _coor) {
    static GLint glCoor[2];
    glCoor[0] = _coor.x();
    glCoor[1] = _coor.y();
    return glCoor;
}

#ifdef MT_DEBUG
void SysGraphics::draw_vector(const Color & _color, const Vector & _vector, const unsigned int _thickness, const unsigned int _arrow_shaft_length, const unsigned int _arrow_head_length) {
    Vector vector = _vector;
    vector.magnitude(_arrow_shaft_length);
    draw_rectangle(_color, Rectangle(vector.magnitude(), _thickness, (vector / 2).destination(), vector.angle()));
    draw_rectangle(_color, Rectangle(_arrow_head_length + (_thickness * 2), _thickness, vector.destination() - Vector(vector.angle() + (PI / 4), _arrow_head_length - _thickness), vector.angle() + (PI / 4)));
    draw_rectangle(_color, Rectangle(_arrow_head_length + (_thickness * 2), _thickness, vector.destination() - Vector(vector.angle() - (PI / 4), _arrow_head_length - _thickness), vector.angle() - (PI / 4)));
}
#endif

void SysGraphics::draw_line(const Color & _color, const Line & _line, const unsigned int _thickness) {
    Vector line_vector(_line.c1(), _line.c2());
    draw_rectangle(_color, Rectangle(line_vector.magnitude(), _thickness, (line_vector / 2).destination(), _line.angle()));
}

void SysGraphics::draw_lines(const Color & _color, const varray<Line> & _lines, const unsigned int _thickness) {
    Colors colors;
    for_range (_lines.size()) colors.push_back(_color);
    draw_lines(colors, _lines, _thickness);
}

void SysGraphics::draw_lines(const Colors & _colors, const varray<Line> & _path, const unsigned int _thickness) {
    Assert::debug(_colors.size() == _path.size(), "varray<Line> Colors size (%i) does not = varray<Line> size (i)", _colors.size(), _path.size());
    for_range (_path.size()) draw_line(_colors[i], _path[i], _thickness);
}

void SysGraphics::draw_triangle(const Color & _color, const Triangle & _triangle, const unsigned int _thickness) {
    draw_triangle(varray<Color>(3, _color), _triangle, _thickness);
}

void SysGraphics::draw_triangle(const Colors & _colors, const Triangle & _triangle, const unsigned int _thickness) {
    Assert::debug(_colors.size() == 3, "Triangle Colors size (%i) does not = 3", _colors.size());
    if (!_thickness) { // draw filled
        glBegin(GL_TRIANGLES);
        glColor(_colors[0]);
        glVertex2iv(glCoordinate(_triangle.c1()));
        glColor(_colors[1]);
        glVertex2iv(glCoordinate(_triangle.c2()));
        glColor(_colors[2]);
        glVertex2iv(glCoordinate(_triangle.c3()));
        glEnd();
    } else {
        draw_lines(_colors, _triangle.lines(), _thickness);
    }
}

void SysGraphics::draw_rectangle(const Color & _color, const Rectangle & _rectangle, const unsigned int _thickness) {
    draw_rectangle(varray<Color>(4, _color), _rectangle, _thickness);
}

void SysGraphics::draw_rectangle(const Colors & _colors, const Rectangle & _rectangle, const unsigned int _thickness) {
    Assert::debug(_colors.size() == 4, "Rectangle Colors size (%i) does not = 4", _colors.size());
    if (!_thickness) { // draw filled
        glBegin(GL_QUADS);
        glColor(_colors[0]);
        glVertex2iv(glCoordinate(_rectangle.top_right()));
        glColor(_colors[1]);
        glVertex2iv(glCoordinate(_rectangle.bottom_right()));
        glColor(_colors[2]);
        glVertex2iv(glCoordinate(_rectangle.bottom_left()));
        glColor(_colors[3]);
        glVertex2iv(glCoordinate(_rectangle.top_left()));
        glEnd();
    } else {
        draw_lines(_colors, _rectangle.lines(), _thickness);
    }
}

void SysGraphics::draw_square(const Color & _color, const Square & _square, const unsigned int _thickness) {
    draw_rectangle(_color, _square, _thickness);
}

void SysGraphics::draw_square(const Colors & _colors, const Square & _square, const unsigned int _thickness) {
    draw_rectangle(_colors, _square, _thickness);
}

void SysGraphics::draw_polygon(const Color & _color, const Polygon & _polygon, const unsigned int _thickness) {
    Colors colors;
    for_range (_polygon.coordinates().size()) colors.push_back(_color);
    draw_polygon(colors, _polygon, _thickness);
}
    
void SysGraphics::draw_polygon(const Colors & _colors, const Polygon & _polygon, const unsigned int _thickness) {
    Assert::debug(_colors.size() == _polygon.coordinates().size(), "Polygon Colors size (%i) does not = Polygon varray<Line> size (%i)", _colors.size(), _polygon.coordinates().size());
    if (!_thickness) { // draw filled
        glBegin(GL_POLYGON);
        for_range (_polygon.coordinates().size()) {
            glColor(_colors[i]);
            glVertex2iv(glCoordinate(_polygon.coordinates()[i]));
        }
        glEnd();
    } else { // draw outline
        draw_lines(_colors, _polygon.lines(), _thickness);
    }
}

void SysGraphics::draw_circle(const Color & _color, const Circle & _circle, const unsigned int _thickness) {
    draw_polygon(_color, Polygon(_circle), _thickness);
}

void SysGraphics::draw_circle(const Colors & _colors, const Circle & _circle, const unsigned int _thickness) {
    draw_polygon(_colors, Polygon(_circle), _thickness);
}

//void SysGraphics::draw_shape(const Color & _color, const Shape & _shape, const unsigned int _thickness) {
//    Colors colors;
//    for_range (_shape.coordinates().size()) colors.push_back(_color);
//    draw_shape(colors, _shape, _thickness);
//}

//void SysGraphics::draw_shape(const Color & _color, const Shape & _shape, const unsigned int _thickness) {
// TODO
//}
