#include "catch.hpp"
#include "mt.hpp"
NAMESPACES

TEST_CASE("float tests", "prove that float_eq,gt,ge,lt,le works") {
    REQUIRE(float_eq(1, 0.999999999));
    REQUIRE(!float_eq(1, 0.999));
}
