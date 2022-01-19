#include "catch.hpp"
#include "mt.hpp"
#include "geometry.hpp"
NAMESPACES

TEST_CASE("circle tests") {
    Circle c;
    
    c = Circle(4, Coordinate(5, 10));
    REQUIRE(c.center() == Coordinate(5, 10));
    REQUIRE(c.radius() == 4);
    REQUIRE(c.diameter() == 8);
    REQUIRE(c.area() == 16 * PI);
    c.move(Vector(8, 12));
    REQUIRE(c.center() == Coordinate(13, 22));
    REQUIRE(c.radius() == 4);
    REQUIRE(c.diameter() == 8);
    REQUIRE(c.area() == 16 * PI);
    c.scale(3, c.center());
    REQUIRE(c.center() == Coordinate(13, 22));
    REQUIRE(c.radius() == 12);
    REQUIRE(c.diameter() == 24);
    REQUIRE(c.area() == 144 * PI);
}

TEST_CASE("polygon tests") {
    Polygon p;
    
    p = Polygon(varray<Coordinate>({ Coordinate(10, 10), Coordinate(0, 10), Coordinate(0, 0), Coordinate(10, 0) }));
    REQUIRE(p.convex());
    
    p = Polygon(varray<Coordinate>({ Coordinate(10, 10), Coordinate(7.5, 10), Coordinate(7.5, 15), Coordinate(2.5, 15), Coordinate(2.5, 10), Coordinate(0, 10), Coordinate(0, 0), Coordinate(10, 0) }));
    REQUIRE(!p.convex());
}
