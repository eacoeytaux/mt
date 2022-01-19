#include "Sprite.hpp"

NAMESPACES
using mt::graphics::Sprite;

Sprite::Sprite(const varray<ColoredPolygon> & _shapes) :
m_shapes(_shapes) { }

varray<Sprite::ColoredPolygon> Sprite::shapes() const {
    return m_shapes;
}

Sprite & Sprite::clear() {
    m_shapes.clear();
    return *this;
}

Sprite & Sprite::add_sprite(const Sprite & _sprite) {
    for_each (gshape, _sprite.m_shapes) m_shapes.push_back(gshape);
    return *this;
}

Sprite & Sprite::add_shape(const ColoredPolygon & _gshape) {
    m_shapes.push_back(_gshape);
    return *this;
}

Sprite & Sprite::add_shape(const Line & _line, const Color & _color, uint _thickness) {
    ColoredPolygon colored_shape;
    colored_shape.shape = Rectangle(_line.length(), max<float>(_thickness, 1), (Vector(_line.c1(), _line.c2()) / 2).destination(), _line.angle());
    colored_shape.colors = varray<Color>(4, _color);
    colored_shape.thickness = FILLED;
    return add_shape(colored_shape);
}

Sprite & Sprite::add_shape(const Shape & _shape, const Color & _color, uint _thickness) {
    ColoredPolygon colored_shape;
    colored_shape.shape = Polygon(_shape.coordinates());
    colored_shape.colors = varray<Color>(4, _color);
    colored_shape.thickness = _thickness;
    return add_shape(colored_shape);
}

Sprite & Sprite::add_shape(const Shape & _shape, const varray<Color> & _colors, uint _thickness) {
    ColoredPolygon colored_shape;
    colored_shape.shape = Polygon(_shape.coordinates());
    colored_shape.colors = _colors;
    colored_shape.thickness = _thickness;
    return add_shape(colored_shape);
}
