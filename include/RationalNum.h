/*  RationalNum.h
 *  This file is a part of the bruteforcefrac library.
 *
 *  Copyright (c) 2019 Paul Ngo
 *
 *  Licensed under the MIT License
 */

#ifndef BRUTEFORCEFRAC_RATIONALNUM_H
#define BRUTEFORCEFRAC_RATIONALNUM_H

#include "IntFactor.h"
#include "IntFactorVector.h"

#include <cstdint>
#include <cstdio>

#include <vector>

#include <stdexcept>

namespace bffrac {

/**
 * @brief A class for handling rational numbers
 *
 * The class consists of unsigned integers for the numerator
 * and denominator, and a bool to store the sign of this RationalNum.
 *
 * @note 0 is represented by 0/1 with isPositive == false.
 * @note Anything with a denominator of 0 is undefined.
 */
class RationalNum {
private:
    uint64_t numerator;
    uint64_t denominator;
    bool isPositive;

public:
    /**
     * Construct a RationalNum using signed integers.
     *
     * @param numerator - The numerator.
     * @param denominator - The denominator (must be nonzero).
     * @throw std::invalid_argument if the denominator is 0.
     */
    RationalNum(int64_t numerator, int64_t denominator = 1) {
        if (denominator == 0) {
            throw std::invalid_argument("RationalNum: received zero denominator");
        }
        else if (numerator == 0) {
            this->numerator = 0;
            this->denominator = 1;
            this->isPositive = false;
        }
        else {
            // Take the absolute value of the params
            this->numerator = (uint64_t) (numerator > 0 ? numerator : -1 * numerator);
            this->denominator = (uint64_t) (denominator > 0 ? denominator : -1 * denominator);

            if ((numerator >= 0 && denominator >= 0) || (numerator < 0 && denominator < 0))
                isPositive = true;
            else
                isPositive = false;
        }
    }

    /**
     * Construct a RationalNum using unsigned integers, explicitly
     * denoting the sign of this RationalNum.
     *
     * @param numerator - The numerator.
     * @param denominator - The denominator (must be nonzero).
     * @param isPositive - The sign.
     * @throw std::invalid_argument if the denominator is 0.
     */
    RationalNum(uint64_t numerator, uint64_t denominator, bool isPositive) {
        if (denominator == 0) {
            throw std::invalid_argument("RationalNum: received zero denominator");
        }
        else if (numerator == 0) {
            this->numerator = 0;
            this->denominator = 1;
            this->isPositive = false;
        }
        else {
            this->numerator = numerator;
            this->denominator = denominator;
            this->isPositive = isPositive;
        }
    }

    /**
     * Return the numerator of this RationalNum.
     * @return numerator
     */
    uint64_t getNumerator() {return numerator;}

    /**
     * Return the denominator of this RationalNum.
     * @return denominator
     */
    uint64_t getDenominator() {return denominator;}

    /**
     * Gets the sign of the rational number
     * @return true if the rational number is positive,
     *         otherwise returns false
     */
    bool positive() {return isPositive;}

    /**
     * Changes the numerator of this RationalNum.
     * @param numerator - The new numerator.
     */
    void setNumerator(uint64_t numerator) {this->numerator = numerator;}

    /**
     * Changes the denominator of this RationalNum.
     * @param denominator - The new denominator.
     */
    void setDenominator(uint64_t denominator) {this->denominator = denominator;}


    /**
     * Changes the sign of this RationalNum.
     * @param isPositive - The new sign of this RationalNum.
     */
    void setPositive(bool isPositive) {this->isPositive = isPositive;}

    /**
     * Simplify the numerator and denominator via prime factorization.
     *
     * @note If the numerator is 0, this function will convert into the
     * zero RationalNum: the nonpositive 0/1.
     */
    void simplify() {
        // Don't simplify easy/undefined fractions such as 1/34636, 14214/1, 0/123, 13/0
        if (numerator > 1 && denominator > 1) {
            // Prime factorize the numerator and denominator
            std::vector<IntFactor*>* numeratorPrimeFactors = primeFactorizeToVector(numerator);
            std::vector<IntFactor*>* denominatorPrimeFactors = primeFactorizeToVector(denominator);

            // Pick the side with the least factors to be the base list for comparison
            // that is, this is the list we loop first in
            std::vector<IntFactor*>* compareBase = (numeratorPrimeFactors->size() <= denominatorPrimeFactors->size())
                    ? numeratorPrimeFactors
                    : denominatorPrimeFactors;

            // The other side is the target list
            std::vector<IntFactor*>* compareTarget = (compareBase == numeratorPrimeFactors)
                    ? denominatorPrimeFactors
                    : numeratorPrimeFactors;

            // Preparing to loop through compareBaseList and cancel common factors
            // between compareBaseList and compareTargetList. This changes
            // numeratorPrimeFactors and denominatorPrimeFactors.
            for (IntFactor* factorFromBaseList : *compareBase) {
                // cancelWithFactor has side effects that also affect factorFromBaseList
                cancelFacVecWithFactor(compareTarget, factorFromBaseList);
            }

            numerator = getValue(numeratorPrimeFactors);
            denominator = getValue(denominatorPrimeFactors);

            delete numeratorPrimeFactors;
            delete denominatorPrimeFactors;
        }

        // 0 is represented by nonpositive 0/1
        if (numerator == 0) {
            denominator = 1;
            isPositive = false;
        }

    }

    /**
     * Adds @p toAdd to this RationalNumber.
     *
     * This RationalNumber is changed and simplified.
     *
     * @example Pseudocode: if x == 1/2 and we run x.add(3/4), then x == 5/4.
     * @param toAdd - The fraction to add to this rational number.
     *
     */
    void add(RationalNum* toAdd) {
        if (toAdd && toAdd->numerator != 0 && toAdd->denominator != 0) {
            // if this has numerator of 0, easy to add
            if (numerator == 0) {
                isPositive = toAdd->isPositive;
                numerator = toAdd->numerator;
                denominator = toAdd->denominator;
            }
            else {
                // To prevent side effects on toAdd, store the value
                // of the numerator in a separate variable
                uint64_t toAddCompatNumerator = toAdd->numerator;

                // need common denominator
                // e.g. to add 1/2 and 1/3, we need to do
                // 1/2 = 1/2 * 3/3 = 3/6 and 1/3 = 1/3 * 2/2 = 2/6.
                // But we can forget about changing toAdd->denominator as
                // it's not used during the actual addition
                if (toAdd->denominator != denominator) {
                    uint64_t oldDenom = denominator;

                    numerator *= toAdd->denominator;
                    denominator *= toAdd->denominator;

                    toAddCompatNumerator *= oldDenom;
                }

                // adding two RationalNums of the same sign
                if ((isPositive && toAdd->isPositive) || (!isPositive && !toAdd->isPositive)) {
                    numerator += toAddCompatNumerator;
                }
                    // adding two RationalNums of different signs
                    // e.g., 434 - 23 is straight forward,
                    // but 23 - 434 = -(423 - 23)
                else {
                    if (numerator >= toAddCompatNumerator) {
                        numerator -= toAddCompatNumerator;
                    } else {
                        isPositive = toAdd->isPositive;
                        numerator = toAddCompatNumerator - numerator;
                    }
                }
            }

            simplify();
        }
    }

    /**
     * Replaces this RationalNum with product of this and @p toMult
     *
     * This RationalNum is changed and simplified.
     *
     * @note If either one of the RatNums has a zero numerator, then
     *       this object will be changed into nonpositive 0/1.
     *
     * @param toMult - The fraction to multiply with
     */
    void multiply(RationalNum* toMult) {
        if (toMult && toMult->denominator != 0) {
            numerator *= toMult->numerator;
            denominator *= toMult->denominator;
            isPositive = (isPositive == toMult->isPositive);

            simplify();
        }
    }

    /**
     * Subtracts @p toSubtr from this rational number.
     * @param toSubtr - The fraction to subtract from rational number.
     */
    void subtract(RationalNum* toSubtr) {
        if (toSubtr) {
            RationalNum* neg_of_toSubtr = new RationalNum(toSubtr->numerator,
                                                          toSubtr->denominator,
                                                          !toSubtr->isPositive);

            add(neg_of_toSubtr);

            delete(neg_of_toSubtr);
        }
    }

    /**
     * Divides this by @p toSubtr.
     * @param toSubtr - The fraction to divide by.
     */
    void divide(RationalNum* toDivide) {
        if (toDivide && toDivide->numerator != 0) {
            RationalNum* reciprocal_of_toDivide = new RationalNum(toDivide->denominator,
                                                                  toDivide->numerator,
                                                                  toDivide->isPositive);
            multiply(reciprocal_of_toDivide);

            delete(reciprocal_of_toDivide);
        }
    }

    /**
     * Mainly a debug print of the rational number
     */
    void print() {
        if (isPositive)
            printf("%" PRIu64 "/%" PRIu64 "\n", getNumerator(), getDenominator() );
        else
            printf("-%" PRIu64 "/%" PRIu64 "\n", getNumerator(), getDenominator() );
    }

};

}

#endif //BRUTEFORCEFRAC_RATIONALNUM_H
