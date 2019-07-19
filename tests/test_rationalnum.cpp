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

SCENARIO( "Sums of rational numbers", "[rationalnum][add]" ) {
    GIVEN( "0/1" ) {
        auto testFrac1 = bffrac::RationalNum(0,1);

        WHEN( "we run (0/1).add(22/15)" ) {
            testFrac1.add(new bffrac::RationalNum(22,15));

            THEN("we get 22/15") {
                REQUIRE(testFrac1.positive());
                REQUIRE(testFrac1.getNumeratorValue() == 22);
                REQUIRE(testFrac1.getDenominatorValue() == 15);
            }
        }

        auto testFrac2 = bffrac::RationalNum(0,1);

        WHEN( "we run (0/1).add(-22/15)" ) {
            testFrac2.add(new bffrac::RationalNum(-22,15));

            THEN("we get -22/15") {
                REQUIRE(!testFrac2.positive());
                REQUIRE(testFrac2.getNumeratorValue() == 22);
                REQUIRE(testFrac2.getDenominatorValue() == 15);
            }
        }
    }

    GIVEN( "2/3" ) {
        auto testAdditiveInverse1 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).add(-2/3) (additive inverse)" ) {
            testAdditiveInverse1.add(new bffrac::RationalNum(-2,3));

            THEN("we get nonpositive 0/1") {
                REQUIRE(!testAdditiveInverse1.positive());
                REQUIRE(testAdditiveInverse1.getNumeratorValue() == 0);
                REQUIRE(testAdditiveInverse1.getDenominatorValue() == 1);
            }
        }

        auto testFrac1 = bffrac::RationalNum(2,3);

        WHEN( "we run (2/3).add(4/5)" ) {
            testFrac1.add(new bffrac::RationalNum(4,5));

            THEN("we get 22/15") {
                REQUIRE(testFrac1.positive());
                REQUIRE(testFrac1.getNumeratorValue() == 22);
                REQUIRE(testFrac1.getDenominatorValue() == 15);
            }
        }

        auto testFrac2 = bffrac::RationalNum(2,3);

        WHEN( "we run (2/3).add(-4/5)" ) {
            testFrac2.add(new bffrac::RationalNum(-4,5));

            THEN("we get -2/15") {
                REQUIRE(!testFrac2.positive());
                REQUIRE(testFrac2.getNumeratorValue() == 2);
                REQUIRE(testFrac2.getDenominatorValue() == 15);
            }
        }

        auto testFrac3 = bffrac::RationalNum(2,3);

        WHEN( "we run (2/3).add(0/5)" ) {
            auto testFrac3add = bffrac::RationalNum(0,5);
            testFrac3.add(&testFrac3add);

            THEN("we get 2/3") {
                REQUIRE(testFrac3.positive());
                REQUIRE(testFrac3.getNumeratorValue() == 2);
                REQUIRE(testFrac3.getDenominatorValue() == 3);
            }
        }
    }

    GIVEN( "-2/3" ) {
        auto testFrac1 = bffrac::RationalNum(-2,3);

        WHEN( "we run (-2/3).add(4/5)" ) {
            testFrac1.add(new bffrac::RationalNum(4,5));

            THEN("we get 2/15") {
                REQUIRE(testFrac1.positive());
                REQUIRE(testFrac1.getNumeratorValue() == 2);
                REQUIRE(testFrac1.getDenominatorValue() == 15);
            }
        }

        auto testFrac2 = bffrac::RationalNum(-2,3);

        WHEN( "we run (-2/3).add(-4/5)" ) {
            testFrac2.add(new bffrac::RationalNum(-4,5));

            THEN("we get -22/15") {
                REQUIRE(!testFrac2.positive());
                REQUIRE(testFrac2.getNumeratorValue() == 22);
                REQUIRE(testFrac2.getDenominatorValue() == 15);
            }
        }

        auto testFrac3 = bffrac::RationalNum(-2,3);

        WHEN( "we run (-2/3).add(0/0)" ) {
            auto testFrac3add = bffrac::RationalNum(0,0);
            testFrac3.add(&testFrac3add);

            THEN("we get -2/3") {
                REQUIRE(!testFrac3.positive());
                REQUIRE(testFrac3.getNumeratorValue() == 2);
                REQUIRE(testFrac3.getDenominatorValue() == 3);
            }
        }
    }

}

SCENARIO( "Products of rational numbers", "[rationalnum][multiply]" ) {
    GIVEN( "2/3" ) {
        auto testFrac1 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).multiply(4/5)" ) {
            testFrac1.multiply(new bffrac::RationalNum(4,5));

            THEN("we get 8/15") {
                REQUIRE(testFrac1.positive());
                REQUIRE(testFrac1.getNumeratorValue() == 8);
                REQUIRE(testFrac1.getDenominatorValue() == 15);
            }
        }

        auto testFrac2 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).multiply(-4/5)" ) {
            testFrac2.multiply(new bffrac::RationalNum(-4,5));

            THEN("we get -8/15") {
                REQUIRE(!testFrac2.positive());
                REQUIRE(testFrac2.getNumeratorValue() == 8);
                REQUIRE(testFrac2.getDenominatorValue() == 15);
            }
        }

        auto testFrac3 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).multiply(3/2)" ) {
            testFrac3.multiply(new bffrac::RationalNum(3,2));

            THEN("we get 1/1") {
                REQUIRE(testFrac3.positive());
                REQUIRE(testFrac3.getNumeratorValue() == 1);
                REQUIRE(testFrac3.getDenominatorValue() == 1);
            }
        }

        auto testFrac4 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).multiply(0,1)" ) {
            testFrac4.multiply(new bffrac::RationalNum(0,1));

            THEN("we get nonpositive 0/1") {
                REQUIRE(!testFrac4.positive());
                REQUIRE(testFrac4.getNumeratorValue() == 0);
                REQUIRE(testFrac4.getDenominatorValue() == 1);
            }
        }
    }

    GIVEN( "0/1" ) {
        auto testFrac1 = bffrac::RationalNum(0,1);
        WHEN("we run (0/1).multiply(4/5)") {
            testFrac1.multiply(new bffrac::RationalNum(4, 5));

            THEN("we get nonpositive 0/1") {
                REQUIRE(!testFrac1.positive());
                REQUIRE(testFrac1.getNumeratorValue() == 0);
                REQUIRE(testFrac1.getDenominatorValue() == 1);
            }
        }

        auto testFrac2 = bffrac::RationalNum(0,1);
        WHEN("we run (0/1).multiply(-4/5)") {
            testFrac1.multiply(new bffrac::RationalNum(-4, 5));

            THEN("we get nonpositive 0/1") {
                REQUIRE(!testFrac2.positive());
                REQUIRE(testFrac2.getNumeratorValue() == 0);
                REQUIRE(testFrac2.getDenominatorValue() == 1);
            }
        }
    }
}
