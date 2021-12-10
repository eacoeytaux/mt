#ifndef __Color__
#define __Color__

#include "mt.hpp"

//#define Colors varray<Color>

namespace mt {

const unsigned int FILLED_ = 0; // used in other graphic classes must be kept 0

class Color {
public:
    Color(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255);
    Color(const Color & c);
    Color(const Color & c, unsigned char a);
    
    unsigned char r() const;
    void r(unsigned char r);
    unsigned char g() const;
    void g(unsigned char g);
    unsigned char b() const;
    void b(unsigned char b);
    unsigned char a() const;
    void a(unsigned char a);
    
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

#endif /* defined(__Color__) */
