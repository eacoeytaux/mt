#ifndef SysGraphics_hpp
#define SysGraphics_hpp

#include "mt.hpp"
#include "Geometry.hpp"
#include "Color.hpp"

namespace mt {
namespace graphics {

enum GRAPHICS_SETTINGS {
    BASIC,
    FANCY
};

/// @class SysGraphics
/// @brief interface for system graphics
class SysGraphics {
public:
    static GRAPHICS_SETTINGS fanciness();
    static bool set_blend_normal();
    static bool set_blend_add();
    static bool show_cursor(bool);
    
    static bool start(uint32_t width, uint32_t height);
    static bool clear(const Color & = BLACK);
    static bool render();
    static bool close();
    
    static void draw_line(const Color &, const Line &, const unsigned int thickness = 1);
    static void draw_lines(const Color &, const varray<Line> &, const unsigned int thickness = 1);
    static void draw_lines(const Colors &, const varray<Line> &, const unsigned int thickness = 1);
    static void draw_triangle(const Color &, const Triangle &, const unsigned int thickness = FILLED);
    static void draw_triangle(const Colors &, const Triangle &, const unsigned int thickness = FILLED);
    static void draw_polygon(const Color &, const Polygon &, const unsigned int thickness = FILLED);
    static void draw_polygon(const Colors &, const Polygon &, const unsigned int thickness = FILLED);

private:
    SysGraphics() { }
    
};

}
}

#endif /* SysGraphics_hpp */
