#include "catch.hpp"

#include "RationalNum.h"

SCENARIO( "Rational numbers have signs", "[rationalnum]" ) {
    WHEN( "we initialize (-5)/2 and 5/(-2)" ) {
        auto testFrac1 = bffrac::RationalNum(-5,2);
        auto testFrac2 = bffrac::RationalNum(5,-2);

        THEN( "the fractions are negative and their individual values are unsigned" ) {
            REQUIRE(testFrac1.getNumeratorValue() == 5);
            REQUIRE(testFrac1.getDenominatorValue() == 2);
            REQUIRE(!testFrac1.positive());

            REQUIRE(testFrac2.getNumeratorValue() == 5);
            REQUIRE(testFrac2.getDenominatorValue() == 2);
            REQUIRE(!testFrac2.positive());
        }
    }

    WHEN( "we initialize -5/-2 and 5/2" ) {
        auto testFrac3 = bffrac::RationalNum(-5,-2);
        auto testFrac4 = bffrac::RationalNum(5,2);

        THEN( "the fractions are positive and their individual values are unsigned" ) {
            REQUIRE(testFrac3.getNumeratorValue() == 5);
            REQUIRE(testFrac3.getDenominatorValue() == 2);
            REQUIRE(testFrac3.positive());

            REQUIRE(testFrac4.getNumeratorValue() == 5);
            REQUIRE(testFrac4.getDenominatorValue() == 2);
            REQUIRE(testFrac4.positive());
        }
    }

    WHEN( "we initialize 40 and -40" ) {
        auto testFrac3 = bffrac::RationalNum(40);
        auto testFrac4 = bffrac::RationalNum(-40);

        THEN( "they are 40/1 and -40/1 respectively" ) {
            REQUIRE(testFrac3.getNumeratorValue() == 40);
            REQUIRE(testFrac3.getDenominatorValue() == 1);
            REQUIRE(testFrac3.positive());

            REQUIRE(testFrac4.getNumeratorValue() == 40);
            REQUIRE(testFrac4.getDenominatorValue() == 1);
            REQUIRE(!testFrac4.positive());
        }
    }

}

SCENARIO( "Rational numbers are simplified", "[rationalnum]" ) {
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

    GIVEN( "The rational number (-875468)/495" ) {
        auto testFrac = bffrac::RationalNum(-875468,495);

        WHEN( "the rational number is simplified" ) {
            testFrac.simplify();

            THEN( "the numerator and denominator are reduced to -79588/45" ) {
                REQUIRE(!testFrac.positive());
                REQUIRE(testFrac.getNumeratorValue() == 79588);
                REQUIRE(testFrac.getDenominatorValue() == 45);
            }
        }
    }

    GIVEN( "The rational number 17179869143/34359738337" ) {
        auto testFrac = bffrac::RationalNum(17179869143, 34359738337);

        WHEN( "the rational number is simplified" ) {
            testFrac.simplify();

            THEN( "it is unchanged as they're both prime" ) {
                REQUIRE(testFrac.getNumeratorValue() == 17179869143);
                REQUIRE(testFrac.getDenominatorValue() == 34359738337);
            }
        }
    }

    GIVEN( "The rational number 6005020/2568973" ) {
        auto testFrac = bffrac::RationalNum(6005020, 2568973);

        WHEN( "the rational number is simplified" ) {
            testFrac.simplify();

            THEN( "it is unchanged as they're both relatively prime" ) {
                REQUIRE(testFrac.getNumeratorValue() == 6005020);
                REQUIRE(testFrac.getDenominatorValue() == 2568973);
            }
        }
    }

    GIVEN( "The rational numbers 500/1 and 1/500" ) {
        auto testFrac1 = bffrac::RationalNum(500,1);
        auto testFrac2 = bffrac::RationalNum(1,500);

        WHEN( "the rational numbers are simplified" ) {
            testFrac1.simplify(); testFrac2.simplify();

            THEN( "the numerators and denominators are unchanged" ) {
                REQUIRE(testFrac1.getNumeratorValue() == 500);
                REQUIRE(testFrac1.getDenominatorValue() == 1);
                REQUIRE(testFrac2.getNumeratorValue() == 1);
                REQUIRE(testFrac2.getDenominatorValue() == 500);
            }
        }
    }

    GIVEN( "The rational numbers 0/1 and 1/0" ) {
        auto testFrac1 = bffrac::RationalNum(0,1);
        auto testFrac2 = bffrac::RationalNum(1,0);

        WHEN( "the rational numbers are simplified" ) {
            testFrac1.simplify(); testFrac2.simplify();

            THEN( "the numerators and denominators are unchanged (and no errors)" ) {
                REQUIRE(testFrac1.getNumeratorValue() == 0);
                REQUIRE(testFrac1.getDenominatorValue() == 1);
                REQUIRE(testFrac2.getNumeratorValue() == 1);
                REQUIRE(testFrac2.getDenominatorValue() == 0);
            }
        }
    }
}
