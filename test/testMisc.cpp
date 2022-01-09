#include "catch.hpp"

#include "mt.hpp"
NAMESPACES

TEST_CASE("meta test", "prove that tests work") {
    REQUIRE("mt");
    REQUIRE(1 == 1);
}

TEST_CASE("float tests", "prove that float_eq,gt,ge,lt,le works") {
    REQUIRE(float_eq(1, 0.99999999));
    REQUIRE(!float_eq(1, 0.99));
}
