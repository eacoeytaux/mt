#include "Shape.hpp"

#include "Triangle.hpp"

NAMESPACES
using mt::geometry::Shape;

bool Shape::operator!=(const Shape & _shape) const { return !(*this == _shape); }
bool Shape::operator==(const Shape & _shape) const {
    if (coordinates().size() != _shape.coordinates().size()) return false;
    for_range(coordinates().size()) if (coordinates()[i] != _shape.coordinates()[i]) return false;
    return true;
}
