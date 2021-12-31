#ifndef SysGraphics_hpp
#define SysGraphics_hpp

#include "mt.hpp"
#include "Geometry.hpp"
#include "Color.hpp"

namespace mt {
namespace graphics {

/// @class SysGraphics
/// @brief interface for system graphics
class SysGraphics {
public:
#ifdef MT_DEBUG
    /// @param arrow_shaft_length length of shaft of vector
    /// @param arrow_head_length length of head of vector
    static void draw_vector(const Color &, const Vector &, const unsigned int thickness = 1, const unsigned int arrow_shaft_length = 50, const unsigned int arrow_head_length = 10);
#endif
    static void draw_line(const Color &, const Line &, const unsigned int thickness = 1);
    static void draw_lines(const Color &, const varray<Line> &, const unsigned int thickness = 1);
    static void draw_lines(const Colors &, const varray<Line> &, const unsigned int thickness = 1);
    static void draw_triangle(const Color &, const Triangle &, const unsigned int thickness = FILLED);
    static void draw_triangle(const Colors &, const Triangle &, const unsigned int thickness = FILLED);
    static void draw_rectangle(const Color &, const Rectangle &, const unsigned int thickness = FILLED);
    static void draw_rectangle(const Colors &, const Rectangle &, const unsigned int thickness = FILLED);
    static void draw_square(const Color &, const Square &, const unsigned int thickness = FILLED);
    static void draw_square(const Colors &, const Square &, const unsigned int thickness = FILLED);
    static void draw_polygon(const Color &, const Polygon &, const unsigned int thickness = FILLED);
    static void draw_polygon(const Colors &, const Polygon &, const unsigned int thickness = FILLED);
    static void draw_circle(const Color &, const Circle &, const unsigned int thickness = FILLED);
    static void draw_circle(const Colors &, const Circle &, const unsigned int thickness = FILLED);
    static void draw_shape(const Color &, const Shape &, const unsigned int thickness = FILLED);
//    static void draw_shape(const Colors &, const Shape &, const unsigned int thickness = FILLED);

private:
    SysGraphics() { }
    
};

}
}

#endif /* SysGraphics_hpp */
