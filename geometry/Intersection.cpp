#include "Intersection.hpp"

NAMESPACES
using mt::geometry::Intersection;

bool Intersection::INTERSECTION_CHECK_FN(const Circle & _c1, const Circle & _c2) {
    return (_c1.center().distance(_c2.center()) <= _c1.radius() + _c2.radius());
}

bool Intersection::INTERSECTION_CHECK_FN(const Circle & _c, const Triangle & _t) {
    return Assert::TODO("intersection check");
}

bool Intersection::INTERSECTION_CHECK_FN(const Circle & _c, const Rectangle & _r) {
    return Assert::TODO("intersection check");
}

bool Intersection::INTERSECTION_CHECK_FN(const Circle & _c, const Polygon & _p) {
    return Assert::TODO("intersection check");
}

// Triangle

bool Intersection::INTERSECTION_CHECK_FN(const Triangle & _t1, const Triangle & _t2) {
    return Assert::TODO("intersection check");
}

bool Intersection::INTERSECTION_CHECK_FN(const Triangle & _t, const Rectangle & _r) {
    return Assert::TODO("intersection check");
}

bool Intersection::INTERSECTION_CHECK_FN(const Triangle & _t, const Polygon & _p) {
    return Assert::TODO("intersection check");
}

// Rectangle

bool Intersection::INTERSECTION_CHECK_FN(const Rectangle & _r1, const Rectangle & _r2) {
    return Assert::TODO("intersection check");
}

bool Intersection::INTERSECTION_CHECK_FN(const Rectangle & _r, const Polygon & _p) {
    return Assert::TODO("intersection check");
}

// Polygon

bool Intersection::INTERSECTION_CHECK_FN(const Polygon & _p1, const Polygon & _p2) {
    return Assert::TODO("intersection check");
}
