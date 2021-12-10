#include "Square.hpp"

using namespace mt;

Square::Square(float _width, const Coordinate & _center, const Angle & _angle) : Rectangle(_width, _width, _center, _angle) { }

void Square::width(const float _width) {
    Rectangle::width(_width);
    Rectangle::height(_width);
}

void Square::height(const float _height) {
    Rectangle::width(_height);
    Rectangle::height(_height);
}
