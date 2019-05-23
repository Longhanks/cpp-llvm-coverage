#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

#include "../util.h"


TEST_CASE("Can detect if an integer is positive") {

    SECTION("Positive integers") {
        int i1 = 1;
        int i2 = 100;
        int i3 = 1337;
        REQUIRE(LLVMCoverage::isPositive(i1));
        REQUIRE(LLVMCoverage::isPositive(i2));
        REQUIRE(LLVMCoverage::isPositive(i3));
    }

    SECTION("Negative integers") {
        int i1 = -1;
        int i2 = -100;
        int i3 = -1337;
        REQUIRE_FALSE(LLVMCoverage::isPositive(i1));
        REQUIRE_FALSE(LLVMCoverage::isPositive(i2));
        REQUIRE_FALSE(LLVMCoverage::isPositive(i3));
    }

    SECTION("Zero") {
        REQUIRE_FALSE(LLVMCoverage::isPositive(0));
    }
}
