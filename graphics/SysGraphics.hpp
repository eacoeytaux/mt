#ifndef SysGraphics_hpp
#define SysGraphics_hpp

#include "mt.hpp"
#include "geometry.hpp"
#include "Color.hpp"

namespace mt {

class SysGraphics {
public:
#ifdef MT_DEBUG
    static void draw_vector(const Color &, const Vector &, const unsigned int thickness = 1, const unsigned int arrow_shaft_length = 50, const unsigned int arrow_head_length = 10);
#endif
    static void draw_line(const Color &, const Line &, const unsigned int thickness = 1);
    static void draw_lines(const Color &, const Path &, const unsigned int thickness = 1); // TODO change to Path
    static void draw_lines(const Colors &, const Path &, const unsigned int thickness = 1); // TODO change to Path
    static void draw_triangle(const Color &, const Triangle &, const unsigned int thickness = FILLED_);
    static void draw_triangle(const Colors &, const Triangle &, const unsigned int thickness = FILLED_);
    static void draw_rectangle(const Color &, const Rectangle &, const unsigned int thickness = FILLED_);
    static void draw_rectangle(const Colors &, const Rectangle &, const unsigned int thickness = FILLED_);
    static void draw_square(const Color &, const Square &, const unsigned int thickness = FILLED_);
    static void draw_square(const Colors &, const Square &, const unsigned int thickness = FILLED_);
    static void draw_polygon(const Color &, const Polygon &, const unsigned int thickness = FILLED_);
    static void draw_polygon(const Colors &, const Polygon &, const unsigned int thickness = FILLED_);
    static void draw_circle(const Color &, const Circle &, const unsigned int thickness = FILLED_);
    static void draw_circle(const Colors &, const Circle &, const unsigned int thickness = FILLED_);
    static void draw_shape(const Color &, const Shape &, const unsigned int thickness = FILLED_);
//    static void draw_shape(const Colors &, const Shape &, const unsigned int thickness = FILLED_);
};

}

#endif /* SysGraphics_hpp */
