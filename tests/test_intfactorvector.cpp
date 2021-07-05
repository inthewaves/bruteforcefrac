#include "test_all_include.h"

namespace {
    SCENARIO("Prime factorizing numbers", "[primefactor]") {
        WHEN("we try to prime factorize 0") {
            REQUIRE(1 == 1);
        }

        WHEN("one tries to create 1/0") {
            THEN("an invalid_argument exception is thrown") {
                bool didExceptionThrow = false;
                try {
                    auto testFrac = bffrac::RationalNum(1, 0);
                }
                catch (const std::invalid_argument &e) {
                    didExceptionThrow = true;
                }
                REQUIRE(didExceptionThrow);
            }
        }
    }

}