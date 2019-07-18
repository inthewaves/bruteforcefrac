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

namespace bruteforcefrac {

/**
 * A class for rational numbers
 */
class RationalNum {
private:
    uint64_t numerator;
    uint64_t denominator;
    bool isPositive;

public:
    RationalNum(int64_t numerator, int64_t denominator) {
        this->numerator = numerator;
        this->denominator = denominator;

        if ( (numerator >= 0 && denominator >= 0) || (numerator < 0 && denominator < 0)) {
            isPositive = true;
        } else isPositive = false;
    }

    uint64_t getNumeratorValue() {return numerator;}

    uint64_t getDenominatorValue() {return denominator;}

    bool positive() {return isPositive;}

    /**
     * Simplify the numerator and denominator via prime factorization.
     */
    void simplify() {
        // Don't simplify easy/undefined fractions such as 1/34636, 14214/1, 0/123, 13/0
        if (numerator > 1 && denominator > 1)
        {
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
            IntFactor* factorFromBaseList;
            for (unsigned long i = 0; i < compareBase->size(); i++) {
                factorFromBaseList = (*compareBase)[i];

                // cancelWithFactor has side effects that also affect factorFromBaseList
                cancelFacVecWithFactor(compareTarget, factorFromBaseList);
            }

            numerator = getValue(numeratorPrimeFactors);
            denominator = getValue(denominatorPrimeFactors);

            delete numeratorPrimeFactors;
            delete denominatorPrimeFactors;
        }
    }

    void print() {
        if (isPositive)
            printf("%" PRIu64 "/%" PRIu64 "\n", getNumeratorValue(), getDenominatorValue() );
        else
            printf("-%" PRIu64 "/%" PRIu64 "\n", getNumeratorValue(), getDenominatorValue() );
    }

};

}

#endif //BRUTEFORCEFRAC_RATIONALNUM_H
