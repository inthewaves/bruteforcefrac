#include "catch.hpp"

#include "RationalNum.h"

SCENARIO( "Rational numbers are simplfied", "[rationalnum]" ) {
    GIVEN( "The rational number 500/250" ) {
        auto testFrac = bffrac::RationalNum(500,250);

        WHEN( "the rational number is simplified" ) {
            testFrac.simplify();

            THEN( "the numerator and denominator are reduced to 2/1" ) {
                REQUIRE(testFrac.getNumeratorValue() == 2);
                REQUIRE(testFrac.getDenominatorValue() == 1);
            }
        }
    }

    GIVEN( "The rational numbers 500/1 and 1/500" ) {
        auto testFrac1 = bffrac::RationalNum(500,1);
        auto testFrac2 = bffrac::RationalNum(1,500);

        WHEN( "the rational numbers are simplified" ) {
            testFrac1.simplify(); testFrac2.simplify();

            THEN( "the numerator and denominator are reduced to 500/1" ) {
                REQUIRE(testFrac1.getNumeratorValue() == 500);
                REQUIRE(testFrac1.getDenominatorValue() == 1);
                REQUIRE(testFrac2.getNumeratorValue() == 1);
                REQUIRE(testFrac2.getDenominatorValue() == 500);
            }
        }
    }
}