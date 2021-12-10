#include "Shape.hpp"

#include "Triangle.hpp"

using namespace mt;

float Shape::area() const { return 0; }
int Shape::sides() const { return (int)this->coordinates().size(); }
varray<Coordinate> Shape::coordinates() const { return { }; }
Path Shape::lines() const { return Path(); }
varray<Triangle> Shape::triangles() const { return varray<Triangle>(); }
void Shape::move(const Vector &) { }

bool Shape::operator!=(const Shape & _shape) const { return !(*this == _shape); }
bool Shape::operator==(const Shape & _shape) const {
    if (coordinates().size() != _shape.coordinates().size()) return false;
    for_range(coordinates().size()) if (coordinates()[i] != _shape.coordinates()[i]) return false;
    return true;
}
