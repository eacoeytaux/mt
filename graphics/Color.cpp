#include "Color.hpp"

using namespace mt;
using mt::graphics::Color;

Color::Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) {
    r(_r);
    g(_g);
    b(_b);
    a(_a);
}

Color::Color(const Color & _c) {
    r(_c.r());
    g(_c.g());
    b(_c.b());
    a(_c.a());
}

Color::Color(const Color & _c, unsigned char _a) {
    r(_c.r());
    g(_c.g());
    b(_c.b());
    a(_a);
}

unsigned char Color::r() const {
    return m_r;
}

Color & Color::r(unsigned char _r) {
    m_r = _r;
    return *this;
}

unsigned char Color::g() const {
    return m_g;
}

Color & Color::g(unsigned char _g) {
    m_g = _g;
    return *this;
}

unsigned char Color::b() const {
    return m_b;
}

Color & Color::b(unsigned char _b) {
    m_b = _b;
    return *this;
}

unsigned char Color::a() const {
    return m_a;
}

Color & Color::a(unsigned char _a) {
    m_a = _a;
    return *this;
}

Color & Color::inverse() {
    m_r = 255 - m_r;
    m_g = 255 - m_g;
    m_b = 255 - m_b;
    return *this;
}

bool Color::operator==(const Color & color) const {
    return ((m_r == color.m_r) && (m_g == color.m_g) && (m_b == color.m_b) && (m_a == color.m_a));
}

bool Color::operator!=(const Color & color) const {
    return !(*this == color);
}
