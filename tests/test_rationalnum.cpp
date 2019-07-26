#include "test_all_include.h"

SCENARIO( "Rational numbers cannot have zero denominator", "[rationalnum]" ) {
    WHEN( "one tries to create 1/0" ) {
        THEN( "an invalid_argument exception is thrown" ) {
            bool didExceptionThrow = false;
            try {
                auto testFrac = bffrac::RationalNum(1,0);
            }
            catch (const std::invalid_argument& e) {
                didExceptionThrow = true;
            }
            REQUIRE(didExceptionThrow);
        }
    }
}

SCENARIO( "Rational numbers have signs", "[rationalnum]" ) {
    WHEN( "we initialize (-5)/2 and 5/(-2)" ) {
        auto testFrac1 = bffrac::RationalNum(-5,2);
        auto testFrac2 = bffrac::RationalNum(5,-2);

        THEN( "the fractions are negative and their individual values are unsigned" ) {
            REQUIRE(testFrac1.getNumerator() == 5);
            REQUIRE(testFrac1.getDenominator() == 2);
            REQUIRE(!testFrac1.positive());

            REQUIRE(testFrac2.getNumerator() == 5);
            REQUIRE(testFrac2.getDenominator() == 2);
            REQUIRE(!testFrac2.positive());
        }
    }

    WHEN( "we initialize -5/-2 and 5/2" ) {
        auto testFrac3 = bffrac::RationalNum(-5,-2);
        auto testFrac4 = bffrac::RationalNum(5,2);

        THEN( "the fractions are positive and their individual values are unsigned" ) {
            REQUIRE(testFrac3.getNumerator() == 5);
            REQUIRE(testFrac3.getDenominator() == 2);
            REQUIRE(testFrac3.positive());

            REQUIRE(testFrac4.getNumerator() == 5);
            REQUIRE(testFrac4.getDenominator() == 2);
            REQUIRE(testFrac4.positive());
        }
    }

    WHEN( "we initialize 40 and -40" ) {
        auto testFrac3 = bffrac::RationalNum(40);
        auto testFrac4 = bffrac::RationalNum(-40);

        THEN( "they are 40/1 and -40/1 respectively" ) {
            REQUIRE(testFrac3.getNumerator() == 40);
            REQUIRE(testFrac3.getDenominator() == 1);
            REQUIRE(testFrac3.positive());

            REQUIRE(testFrac4.getNumerator() == 40);
            REQUIRE(testFrac4.getDenominator() == 1);
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
                REQUIRE(testFrac.getNumerator() == 2);
                REQUIRE(testFrac.getDenominator() == 1);
            }
        }
    }

    GIVEN( "The rational number (-875468)/495" ) {
        auto testFrac = bffrac::RationalNum(-875468,495);

        WHEN( "the rational number is simplified" ) {
            testFrac.simplify();

            THEN( "the numerator and denominator are reduced to -79588/45" ) {
                REQUIRE(!testFrac.positive());
                REQUIRE(testFrac.getNumerator() == 79588);
                REQUIRE(testFrac.getDenominator() == 45);
            }
        }
    }

    GIVEN( "The rational number 17179869143/34359738337" ) {
        auto testFrac = bffrac::RationalNum(17179869143, 34359738337);

        WHEN( "the rational number is simplified" ) {
            testFrac.simplify();

            THEN( "it is unchanged as they're both prime" ) {
                REQUIRE(testFrac.getNumerator() == 17179869143);
                REQUIRE(testFrac.getDenominator() == 34359738337);
            }
        }
    }

    GIVEN( "The rational number 6005020/2568973" ) {
        auto testFrac = bffrac::RationalNum(6005020, 2568973);

        WHEN( "the rational number is simplified" ) {
            testFrac.simplify();

            THEN( "it is unchanged as they're both relatively prime" ) {
                REQUIRE(testFrac.getNumerator() == 6005020);
                REQUIRE(testFrac.getDenominator() == 2568973);
            }
        }
    }

    GIVEN( "The rational numbers 500/1 and 1/500" ) {
        auto testFrac1 = bffrac::RationalNum(500,1);
        auto testFrac2 = bffrac::RationalNum(1,500);

        WHEN( "the rational numbers are simplified" ) {
            testFrac1.simplify(); testFrac2.simplify();

            THEN( "the numerators and denominators are unchanged" ) {
                REQUIRE(testFrac1.getNumerator() == 500);
                REQUIRE(testFrac1.getDenominator() == 1);
                REQUIRE(testFrac2.getNumerator() == 1);
                REQUIRE(testFrac2.getDenominator() == 500);
            }
        }
    }

    GIVEN( "The rational numbers 0/65" ) {
        auto testFrac1 = bffrac::RationalNum(0,65);

        WHEN( "the rational numbers is simplified" ) {
            testFrac1.simplify();

            THEN( "0/65 is changed into the nonpositive 0/1" ) {
                REQUIRE(!testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 0);
                REQUIRE(testFrac1.getDenominator() == 1);
            }
        }
    }
}

SCENARIO( "Sums of rational numbers", "[rationalnum][add]" ) {
    GIVEN( "0/1" ) {
        auto testFrac0 = bffrac::RationalNum(0,1);

        WHEN( "we run (0/1).add(0/5)" ) {
            auto testx0 = bffrac::RationalNum(0,5);
            testFrac0.add(&testx0);

            THEN("we get nonegative 0/1") {
                REQUIRE(!testFrac0.positive());
                REQUIRE(testFrac0.getNumerator() == 0);
                REQUIRE(testFrac0.getDenominator() == 1);
            }
        }

        auto testFrac1 = bffrac::RationalNum(0,1);

        WHEN( "we run (0/1).add(22/15)" ) {
            auto testx1 = bffrac::RationalNum(22,15);
            testFrac1.add(&testx1);

            THEN("we get 22/15") {
                REQUIRE(testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 22);
                REQUIRE(testFrac1.getDenominator() == 15);
            }
        }

        auto testFrac2 = bffrac::RationalNum(0,1);

        WHEN( "we run (0/1).add(-22/15)" ) {
            auto testx2 = bffrac::RationalNum(-22,15);
            testFrac2.add(&testx2);

            THEN("we get -22/15") {
                REQUIRE(!testFrac2.positive());
                REQUIRE(testFrac2.getNumerator() == 22);
                REQUIRE(testFrac2.getDenominator() == 15);
            }
        }
    }

    GIVEN( "2/3" ) {
        auto testAdditiveInverse1 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).add(-2/3) (additive inverse)" ) {
            auto testx0 = bffrac::RationalNum(-2,3);
            testAdditiveInverse1.add(&testx0);

            THEN("we get nonpositive 0/1") {
                REQUIRE(!testAdditiveInverse1.positive());
                REQUIRE(testAdditiveInverse1.getNumerator() == 0);
                REQUIRE(testAdditiveInverse1.getDenominator() == 1);
            }
        }

        auto testAdditiveInverse2 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).add(-16/24) (additive inverse)" ) {
            auto testx01 = bffrac::RationalNum(-16,24);
            testAdditiveInverse2.add(&testx01);

            THEN("we get nonpositive 0/1") {
                REQUIRE(!testAdditiveInverse2.positive());
                REQUIRE(testAdditiveInverse2.getNumerator() == 0);
                REQUIRE(testAdditiveInverse2.getDenominator() == 1);
            }
        }

        auto testFrac1 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).add(4/5)" ) {
            auto testx1 = bffrac::RationalNum(4,5);
            testFrac1.add(&testx1);

            THEN("we get 22/15") {
                REQUIRE(testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 22);
                REQUIRE(testFrac1.getDenominator() == 15);
            }
        }

        auto testFrac2 = bffrac::RationalNum(2,3);

        WHEN( "we run (2/3).add(-4/5)" ) {
            auto testx2 = bffrac::RationalNum(-4,5);
            testFrac2.add(&testx2);

            THEN("we get -2/15") {
                REQUIRE(!testFrac2.positive());
                REQUIRE(testFrac2.getNumerator() == 2);
                REQUIRE(testFrac2.getDenominator() == 15);
            }
        }

        auto testFrac3 = bffrac::RationalNum(2,3);

        WHEN( "we run (2/3).add(0/5)" ) {
            auto testx3 = bffrac::RationalNum(0,5);
            testFrac3.add(&testx3);

            THEN("we get 2/3") {
                REQUIRE(testFrac3.positive());
                REQUIRE(testFrac3.getNumerator() == 2);
                REQUIRE(testFrac3.getDenominator() == 3);
            }
        }
    }

    GIVEN( "-2/3" ) {

        auto testAdditiveInverse1 = bffrac::RationalNum(-2,3);
        WHEN( "we run (-2/3).add(2/3) (additive inverse)" ) {
            auto testx0 = bffrac::RationalNum(2,3);
            testAdditiveInverse1.add(&testx0);

            THEN("we get nonpositive 0/1") {
                REQUIRE(!testAdditiveInverse1.positive());
                REQUIRE(testAdditiveInverse1.getNumerator() == 0);
                REQUIRE(testAdditiveInverse1.getDenominator() == 1);
            }
        }

        auto testAdditiveInverse2 = bffrac::RationalNum(-2,3);
        WHEN( "we run (-2/3).add(16/24) (additive inverse)" ) {
            auto testx01 = bffrac::RationalNum(16,24);
            testAdditiveInverse2.add(&testx01);

            THEN("we get nonpositive 0/1") {
                REQUIRE(!testAdditiveInverse2.positive());
                REQUIRE(testAdditiveInverse2.getNumerator() == 0);
                REQUIRE(testAdditiveInverse2.getDenominator() == 1);
            }
        }

        auto testFrac1 = bffrac::RationalNum(-2,3);

        WHEN( "we run (-2/3).add(4/5)" ) {
            auto testx1 = bffrac::RationalNum(4,5);
            testFrac1.add(&testx1);

            THEN("we get 2/15") {
                REQUIRE(testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 2);
                REQUIRE(testFrac1.getDenominator() == 15);
            }
        }

        auto testFrac2 = bffrac::RationalNum(-2,3);

        WHEN( "we run (-2/3).add(-4/5)" ) {
            auto testx2 = bffrac::RationalNum(-4,5);
            testFrac2.add(&testx2);

            THEN("we get -22/15") {
                REQUIRE(!testFrac2.positive());
                REQUIRE(testFrac2.getNumerator() == 22);
                REQUIRE(testFrac2.getDenominator() == 15);
            }
        }

        auto testFrac3 = bffrac::RationalNum(-2,3);

        WHEN( "we run (-2/3).add(0/13)" ) {
            auto testx3 = bffrac::RationalNum(0,13);
            testFrac3.add(&testx3);

            THEN("we get -2/3") {
                REQUIRE(!testFrac3.positive());
                REQUIRE(testFrac3.getNumerator() == 2);
                REQUIRE(testFrac3.getDenominator() == 3);
            }
        }
    }

    GIVEN( "5/10" ) {
        auto testNoSideEffect = bffrac::RationalNum(5, 10);
        WHEN("we run (5/10).add(-2/3)") {
            auto testNoSideEffect_add = bffrac::RationalNum(-2,3);
            testNoSideEffect.add(&testNoSideEffect_add);

            THEN("we get -1/6") {
                REQUIRE(!testNoSideEffect.positive());
                REQUIRE(testNoSideEffect.getNumerator() == 1);
                REQUIRE(testNoSideEffect.getDenominator() == 6);
            }

            AND_THEN("no side effects on -2/3") {
                REQUIRE(!testNoSideEffect_add.positive());
                REQUIRE(testNoSideEffect_add.getNumerator() == 2);
                REQUIRE(testNoSideEffect_add.getDenominator() == 3);
            }
        }
    }

}

SCENARIO( "Products of rational numbers", "[rationalnum][multiply]" ) {
    GIVEN( "2/3" ) {
        auto testFrac1 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).multiply(4/5)" ) {
            auto testx = bffrac::RationalNum(4,5);
            testFrac1.multiply(&testx);

            THEN("we get 8/15") {
                REQUIRE(testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 8);
                REQUIRE(testFrac1.getDenominator() == 15);
            }
        }

        auto testFrac2 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).multiply(-4/5)" ) {
            auto testx = bffrac::RationalNum(-4,5);
            testFrac2.multiply(&testx);

            THEN("we get -8/15") {
                REQUIRE(!testFrac2.positive());
                REQUIRE(testFrac2.getNumerator() == 8);
                REQUIRE(testFrac2.getDenominator() == 15);
            }
        }

        auto testFrac3 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).multiply(3/2) (multiplicative inverse)" ) {
            auto testx = bffrac::RationalNum(3,2);
            testFrac3.multiply(&testx);

            THEN("we get 1/1") {
                REQUIRE(testFrac3.positive());
                REQUIRE(testFrac3.getNumerator() == 1);
                REQUIRE(testFrac3.getDenominator() == 1);
            }
        }

        auto testFrac4 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).multiply(0,1)" ) {
            auto testx = bffrac::RationalNum(0,1);
            testFrac4.multiply(&testx);

            THEN("we get nonpositive 0/1") {
                REQUIRE(!testFrac4.positive());
                REQUIRE(testFrac4.getNumerator() == 0);
                REQUIRE(testFrac4.getDenominator() == 1);
            }
        }

        auto testFrac5 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).multiply(-1)" ) {
            auto testx = bffrac::RationalNum(-1);
            testFrac5.multiply(&testx);

            THEN("we get -2/3") {
                REQUIRE(!testFrac5.positive());
                REQUIRE(testFrac5.getNumerator() == 2);
                REQUIRE(testFrac5.getDenominator() == 3);
            }
        }
    }

    GIVEN( "-2/3" ) {
        auto testFrac1 = bffrac::RationalNum(-2, 3);

        WHEN( "we run (2/3).multiply(-1)" ) {
            auto testx = bffrac::RationalNum(-1);
            testFrac1.multiply(&testx);

            THEN("we get 2/3") {
                REQUIRE(testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 2);
                REQUIRE(testFrac1.getDenominator() == 3);
            }
        }
    }

    GIVEN( "0/1" ) {
        auto testFrac1 = bffrac::RationalNum(0,1);
        WHEN("we run (0/1).multiply(4/5)") {
            auto testx = bffrac::RationalNum(4, 5);
            testFrac1.multiply(&testx);

            THEN("we get nonpositive 0/1") {
                REQUIRE(!testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 0);
                REQUIRE(testFrac1.getDenominator() == 1);
            }
        }

        auto testFrac2 = bffrac::RationalNum(0,1);
        WHEN("we run (0/1).multiply(-4/5)") {
            auto testx = bffrac::RationalNum(-4, 5);
            testFrac1.multiply(&testx);

            THEN("we get nonpositive 0/1") {
                REQUIRE(!testFrac2.positive());
                REQUIRE(testFrac2.getNumerator() == 0);
                REQUIRE(testFrac2.getDenominator() == 1);
            }
        }
    }
}

SCENARIO( "Quotients of rational numbers", "[rationalnum][divide]" ) {
    GIVEN( "2/3" ) {
        auto testFrac1 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).divide(4/5)" ) {
            auto testx = bffrac::RationalNum(4,5);
            testFrac1.divide(&testx);

            THEN("we get 5/6") {
                REQUIRE(testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 5);
                REQUIRE(testFrac1.getDenominator() == 6);
            }
        }

        auto testFrac2 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).divide(-4/5)" ) {
            auto testx = bffrac::RationalNum(-4,5);
            testFrac2.divide(&testx);

            THEN("we get -5/6") {
                REQUIRE(!testFrac2.positive());
                REQUIRE(testFrac2.getNumerator() == 5);
                REQUIRE(testFrac2.getDenominator() == 6);
            }
        }

        auto testFrac3 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).divide(2/3) (multiplicative inverse)" ) {
            auto testx = bffrac::RationalNum(2,3);
            testFrac3.divide(&testx);

            THEN("we get 1/1") {
                REQUIRE(testFrac3.positive());
                REQUIRE(testFrac3.getNumerator() == 1);
                REQUIRE(testFrac3.getDenominator() == 1);
            }
        }

        auto testFrac5 = bffrac::RationalNum(2,3);
        WHEN( "we run (2/3).divide(-1)" ) {
            auto testx = bffrac::RationalNum(-1);
            testFrac5.divide(&testx);

            THEN("we get -2/3") {
                REQUIRE(!testFrac5.positive());
                REQUIRE(testFrac5.getNumerator() == 2);
                REQUIRE(testFrac5.getDenominator() == 3);
            }
        }
    }

    GIVEN( "0/1" ) {
        auto testFrac1 = bffrac::RationalNum(0, 1);
        WHEN("we run (0/1).divide(-1)") {
            auto testx = bffrac::RationalNum(-1);
            testFrac1.divide(&testx);

            THEN("we get nonnegative 0/1") {
                REQUIRE(!testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 0);
                REQUIRE(testFrac1.getDenominator() == 1);
            }
        }
    }
}

SCENARIO( "Differences of rational numbers", "[rationalnum][subtract]" ) {
    GIVEN( "0/1" ) {
        auto testFrac0 = bffrac::RationalNum(0,1);

        WHEN( "we run (0/1).subtract(0/5)" ) {
            auto testx = bffrac::RationalNum(0,5);
            testFrac0.subtract(&testx);

            THEN("we get nonegative 0/1") {
                REQUIRE(!testFrac0.positive());
                REQUIRE(testFrac0.getNumerator() == 0);
                REQUIRE(testFrac0.getDenominator() == 1);
            }
        }

        auto testFrac1 = bffrac::RationalNum(0,1);

        WHEN( "we run (0/1).subtract(22/15)" ) {
            auto testx = bffrac::RationalNum(22,15);
            testFrac1.subtract(&testx);

            THEN("we get -22/15") {
                REQUIRE(!testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 22);
                REQUIRE(testFrac1.getDenominator() == 15);
            }
        }

        auto testFrac2 = bffrac::RationalNum(0,1);

        WHEN( "we run (0/1).subtract(-22/15)" ) {
            auto testx = bffrac::RationalNum(-22,15);
            testFrac2.subtract(&testx);

            THEN("we get 22/15") {
                REQUIRE(testFrac2.positive());
                REQUIRE(testFrac2.getNumerator() == 22);
                REQUIRE(testFrac2.getDenominator() == 15);
            }
        }
    }

    GIVEN( "2/3" ) {
        auto testAdditiveInverse1 = bffrac::RationalNum(2,3);

        WHEN( "we run (2/3).subtract(2/3)" ) {
            auto testx0 = bffrac::RationalNum(2,3);
            testAdditiveInverse1.subtract(&testx0);

            THEN("we get nonnegative 0/1") {
                REQUIRE(!testAdditiveInverse1.positive());
                REQUIRE(testAdditiveInverse1.getNumerator() == 0);
                REQUIRE(testAdditiveInverse1.getDenominator() == 1);
            }
        }

        auto testFrac1 = bffrac::RationalNum(2,3);

        WHEN( "we run (2/3).add(4/5)" ) {
            auto testx1 = bffrac::RationalNum(4,5);
            testFrac1.subtract(&testx1);

            THEN("we get -2/15") {
                REQUIRE(!testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 2);
                REQUIRE(testFrac1.getDenominator() == 15);
            }
        }

        auto testFrac2 = bffrac::RationalNum(2,3);

        WHEN( "we run (2/3).subtract(-4/5)" ) {
            auto testx2 = bffrac::RationalNum(-4,5);
            testFrac2.subtract(&testx2);

            THEN("we get 22/15") {
                REQUIRE(testFrac2.positive());
                REQUIRE(testFrac2.getNumerator() == 22);
                REQUIRE(testFrac2.getDenominator() == 15);
            }
        }

        auto testFrac3 = bffrac::RationalNum(2,3);

        WHEN( "we run (2/3).subtract(0/5)" ) {
            auto testFrac3add = bffrac::RationalNum(0,5);
            testFrac3.subtract(&testFrac3add);

            THEN("we get 2/3") {
                REQUIRE(testFrac3.positive());
                REQUIRE(testFrac3.getNumerator() == 2);
                REQUIRE(testFrac3.getDenominator() == 3);
            }
        }
    }

    GIVEN( "-2/3" ) {
        auto testAdditiveInverse1 = bffrac::RationalNum(-2,3);

        WHEN( "we run (-2/3).subtract(-2/3)" ) {
            auto testx0 = bffrac::RationalNum(-2,3);
            testAdditiveInverse1.subtract(&testx0);

            THEN("we get nonnegative 0/1") {
                REQUIRE(!testAdditiveInverse1.positive());
                REQUIRE(testAdditiveInverse1.getNumerator() == 0);
                REQUIRE(testAdditiveInverse1.getDenominator() == 1);
            }
        }

        auto testFrac1 = bffrac::RationalNum(-2,3);

        WHEN( "we run (-2/3).subtract(4/5)" ) {
            auto testx1 = bffrac::RationalNum(4,5);
            testFrac1.subtract(&testx1);

            THEN("we get -22/15") {
                REQUIRE(!testFrac1.positive());
                REQUIRE(testFrac1.getNumerator() == 22);
                REQUIRE(testFrac1.getDenominator() == 15);
            }
        }

        auto testFrac2 = bffrac::RationalNum(-2,3);

        WHEN( "we run (-2/3).subtract(-4/5)" ) {
            auto testx2 = bffrac::RationalNum(-4,5);
            testFrac2.subtract(&testx2);

            THEN("we get 2/15") {
                REQUIRE(testFrac2.positive());
                REQUIRE(testFrac2.getNumerator() == 2);
                REQUIRE(testFrac2.getDenominator() == 15);
            }
        }

        auto testFrac3 = bffrac::RationalNum(-2,3);

        WHEN( "we run (-2/3).subtract(0/1)" ) {
            auto testx3 = bffrac::RationalNum(0,1);
            testFrac3.subtract(&testx3);

            THEN("we get -2/3") {
                REQUIRE(!testFrac3.positive());
                REQUIRE(testFrac3.getNumerator() == 2);
                REQUIRE(testFrac3.getDenominator() == 3);
            }
        }
    }
}


