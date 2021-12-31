#ifndef __Color__
#define __Color__

#include "mt.hpp"

//#define Colors varray<Color>

namespace mt {
namespace graphics {

/// @brief used in other graphic classes, must be kept 0
const unsigned int FILLED = 0;

/// @class Color
/// @brief color defined in red, green, blue, and alpha
class Color {
public:
    /// @param r red [0, 255]
    /// @param g green [0, 255]
    /// @param b blue [0, 255]
    /// @param a alpha [0, 255]
    Color(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255);
    /// @param c color
    Color(const Color & c);
    /// @param c color
    /// @param a new alpha
    Color(const Color & c, unsigned char a);
    
    /// @return red
    unsigned char r() const;
    /// @param r red
    void r(unsigned char r);
    /// @return green
    unsigned char g() const;
    /// @param g green
    void g(unsigned char g);
    /// @return blue
    unsigned char b() const;
    /// @param b blue
    void b(unsigned char b);
    /// @return alpha
    unsigned char a() const;
    /// @param a alpha
    void a(unsigned char a);
    
    /// @brief inverse all RGB values i.e. value = (255 - value)
    void inverse();
    
    bool operator==(const Color &) const;
    bool operator!=(const Color &) const;
    
private:
    unsigned char m_r; //red value
    unsigned char m_g; //green value
    unsigned char m_b; //blue value
    unsigned char m_a; //alpha value
};

typedef varray<Color> Colors;

const Color WHITE(255, 255, 255);
const Color GRAY_LIGHT(192, 192, 192);
const Color GRAY_MID(127, 127, 127);
const Color GRAY_DARK(64, 64, 64);
const Color BLACK(0, 0, 0);

const Color RED(255, 0, 0);
const Color GREEN(0, 255, 0);
const Color BLUE(0, 0, 255);

const Color CYAN(0, 255, 255);
const Color MAGENTA(255, 0, 255);
const Color YELLOW(255, 255, 0);

}
}

#endif /* defined(__Color__) */
