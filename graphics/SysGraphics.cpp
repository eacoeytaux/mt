#include "SysGraphics.hpp"

#define GL_SILENCE_DEPRECATION

#if defined(__APPLE__)
#include <SDL2/SDL.h>
#else
#endif

NAMESPACES
using mt::graphics::SysGraphics;

SDL_Window * WINDOW;
uint32_t WINDOW_WIDTH;
uint32_t WINDOW_HEIGHT;
SDL_Renderer * RENDERER;

static GRAPHICS_SETTINGS SETTINGS;

GRAPHICS_SETTINGS SysGraphics::fanciness() {
    return SETTINGS;
}

bool SysGraphics::set_blend_normal() {
    SDL_SetRenderDrawBlendMode(RENDERER, SDL_BLENDMODE_BLEND);
    return true;
}

bool SysGraphics::set_blend_add() {
    SDL_SetRenderDrawBlendMode(RENDERER, SDL_BLENDMODE_ADD);
    return true;
}

bool SysGraphics::show_cursor(const bool _show) {
    if (_show) SDL_ShowCursor(SDL_ENABLE);
    else SDL_ShowCursor(SDL_DISABLE);
    return true;
}

bool SysGraphics::start(uint32_t _width, uint32_t _height) {
    WINDOW_WIDTH = _width;
    WINDOW_HEIGHT = _height;
    WINDOW = SDL_CreateWindow("MT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    RENDERER = SDL_CreateRenderer(WINDOW, -1, 0);
    return set_blend_normal() && show_cursor(false);
}

bool SysGraphics::clear(const Color & _color) {
    SDL_SetRenderDrawColor(RENDERER, _color.r(), _color.g(), _color.b(), SDL_ALPHA_OPAQUE);
    SDL_RenderClear(RENDERER);
    return true;
}

bool SysGraphics::render() {
    SDL_RenderPresent(RENDERER);
    return true;
}

bool SysGraphics::close() {
    return true;
}

void SysGraphics::draw_line(const Color & _color, const Line & _line, const unsigned int _thickness) {
    Vector line_vector(_line.c1(), _line.c2());
    draw_polygon(_color, Rectangle(line_vector.magnitude(), _thickness, (line_vector / 2).destination(), _line.angle()));
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
        uint32_t vert_count = 3;
        SDL_Vertex vert[vert_count];
        
        vert[0].position.x = _triangle.c1().x();
        vert[0].position.y = WINDOW_HEIGHT - _triangle.c1().y();
        vert[0].color.r = _colors[0].r();
        vert[0].color.g = _colors[0].g();
        vert[0].color.b = _colors[0].b();
        vert[0].color.a = _colors[0].a();
        
        vert[1].position.x = _triangle.c2().x();
        vert[1].position.y = WINDOW_HEIGHT - _triangle.c2().y();
        vert[1].color.r = _colors[1].r();
        vert[1].color.g = _colors[1].g();
        vert[1].color.b = _colors[1].b();
        vert[1].color.a = _colors[1].a();
        
        vert[2].position.x = _triangle.c3().x();
        vert[2].position.y = WINDOW_HEIGHT - _triangle.c3().y();
        vert[2].color.r = _colors[2].r();
        vert[2].color.g = _colors[2].g();
        vert[2].color.b = _colors[2].b();
        vert[2].color.a = _colors[2].a();
        
        SDL_RenderGeometry(RENDERER, NULL, vert, vert_count, NULL, 0);
    } else {
        draw_lines(_colors, _triangle.lines(), _thickness);
    }
}

//void SysGraphics::draw_rectangle(const Color & _color, const Rectangle & _rectangle, const unsigned int _thickness) {
//    draw_rectangle(varray<Color>(4, _color), _rectangle, _thickness);
//}
//
//void SysGraphics::draw_rectangle(const Colors & _colors, const Rectangle & _rectangle, const unsigned int _thickness) {
//    Assert::debug(_colors.size() == 4, "Rectangle Colors size (%i) does not = 4", _colors.size());
//    if (!_thickness) { // draw filled
//        varray<Coordinate> rect_coors = _rectangle.coordinates();
//        draw_triangle({ _colors[0], _colors[1], _colors[2] }, Triangle({ rect_coors[0], rect_coors[1], rect_coors[2] }));
//        draw_triangle({ _colors[2], _colors[3], _colors[0] }, Triangle({ rect_coors[2], rect_coors[3], rect_coors[0] }));
//    } else {
//        draw_lines(_colors, _rectangle.lines(), _thickness);
//    }
//}
//
//void SysGraphics::draw_square(const Color & _color, const Square & _square, const unsigned int _thickness) {
//    draw_rectangle(_color, _square, _thickness);
//}
//
//void SysGraphics::draw_square(const Colors & _colors, const Square & _square, const unsigned int _thickness) {
//    draw_rectangle(_colors, _square, _thickness);
//}
//
void SysGraphics::draw_polygon(const Color & _color, const Polygon & _polygon, const unsigned int _thickness) {
    Colors colors;
    for_range (_polygon.coordinates().size()) colors.push_back(_color);
    draw_polygon(colors, _polygon, _thickness);
}

void SysGraphics::draw_polygon(const Colors & _colors, const Polygon & _polygon, const unsigned int _thickness) {
    Assert::debug(_colors.size() == _polygon.coordinates().size(), "Polygon Colors size (%i) does not = Polygon varray<Line> size (%i)", _colors.size(), _polygon.coordinates().size());
    if (!_thickness) { // draw filled
        for_range (_polygon.triangles().size()) {
            Triangle triangle = _polygon.triangles()[i];
            draw_triangle({ _colors[0], _colors[i + 1], _colors[i + 2] }, triangle);
        }
    } else { // draw outline
        draw_lines(_colors, _polygon.lines(), _thickness);
    }
}
//
//void SysGraphics::draw_circle(const Color & _color, const Circle & _circle, const unsigned int _thickness) {
//    draw_polygon(_color, Polygon(_circle), _thickness);
//}
//
//void SysGraphics::draw_circle(const Colors & _colors, const Circle & _circle, const unsigned int _thickness) {
//    draw_polygon(_colors, Polygon(_circle), _thickness);
//}
//
//void SysGraphics::draw_shape(const Color & _color, const Shape & _shape, const unsigned int _thickness) {
//    Colors colors;
//    for_range (_shape.coordinates().size()) colors.push_back(_color);
//    draw_shape(colors, _shape, _thickness);
//}
//
//void SysGraphics::draw_shape(const Colors & _colors, const Shape & _shape, const unsigned int _thickness) {
//    draw_polygon(_colors, Polygon(_shape.coordinates()), _thickness);
//}
