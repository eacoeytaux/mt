#ifndef Intersection_hpp
#define Intersection_hpp

#include "mt.hpp"
#include "Circle.hpp"
#include "Shape.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Square.hpp"
#include "Polygon.hpp"

namespace mt {
namespace geometry {

#define INTERSECTION_CHECK_FN b

/// @class Intersection
/// @brief template file
class Intersection {
public:
    // Circle
    
    static bool INTERSECTION_CHECK_FN(const Circle & c1, const Circle & c2);
    
    static bool INTERSECTION_CHECK_FN(const Circle & c, const Triangle & t);
    static bool INTERSECTION_CHECK_FN(const Triangle & t, const Circle & c) { return INTERSECTION_CHECK_FN(c, t); }
    
    static bool INTERSECTION_CHECK_FN(const Circle & c, const Rectangle & r);
    static bool INTERSECTION_CHECK_FN(const Rectangle & r, const Circle & c) { return INTERSECTION_CHECK_FN(c, r); }
    
    static bool INTERSECTION_CHECK_FN(const Circle & c, const Polygon & p);
    static bool INTERSECTION_CHECK_FN(const Polygon & p, const Circle & c) { return INTERSECTION_CHECK_FN(c, p); }
    
    // Triangle

    static bool INTERSECTION_CHECK_FN(const Triangle & t1, const Triangle & t2);
    
    static bool INTERSECTION_CHECK_FN(const Triangle & t, const Rectangle & r);
    static bool INTERSECTION_CHECK_FN(const Rectangle & r, const Triangle & t) { return INTERSECTION_CHECK_FN(t, r); }
    
    static bool INTERSECTION_CHECK_FN(const Triangle & t, const Polygon & p);
    static bool INTERSECTION_CHECK_FN(const Polygon & p, const Triangle & t) { return INTERSECTION_CHECK_FN(t, p); }
    
    // Rectangle
    
    static bool INTERSECTION_CHECK_FN(const Rectangle & r1, const Rectangle & r2);
    
    static bool INTERSECTION_CHECK_FN(const Rectangle & r, const Polygon & p);
    static bool INTERSECTION_CHECK_FN(const Polygon & p, const Rectangle & r) { return INTERSECTION_CHECK_FN(r, p); }
    
    // Polygon
    
    static bool INTERSECTION_CHECK_FN(const Polygon & p1, const Polygon & p2);
    
private:
    /// @brief constructor should never be called
    Intersection();
};

}
}

#endif /* Intersection_hpp */
