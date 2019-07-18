/*  RationalNum.h
 *  This file is a part of the bruteforcefrac library.
 *
 *  Copyright (c) 2019 Paul Ngo
 *
 *  Licensed under the MIT License
 */

#ifndef BRUTEFORCEFRAC_RATIONALNUM_H
#define BRUTEFORCEFRAC_RATIONALNUM_H

#include "IntFactorList/IntFactorList.h"
#include "IntFactor.h"

#include <cstdint>


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
        // this->numerator->primeFactorize( (numerator < 0) ? -1*numerator : numerator );

        this->denominator = denominator;
        // this->denominator->primeFactorize( (denominator < 0) ? -1*denominator : denominator );

        if ( (numerator >= 0 && denominator >= 0) || (numerator < 0 && denominator < 0)) {
            isPositive = true;
        } else isPositive = false;
    }

    IntFactorList* getNumeratorPrimeFactors() {
        IntFactorList* numeratorFactorList = new IntFactorList();
        numeratorFactorList->primeFactorize( numerator );
        return numeratorFactorList;
    }

    IntFactorList* getDenominatorPrimeFactors() {
        IntFactorList* denominatorFactorList = new IntFactorList();
        denominatorFactorList->primeFactorize( denominator );
        return denominatorFactorList;
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
            IntFactorList* numeratorFactorList = getNumeratorPrimeFactors();
            IntFactorList* denominatorFactorList = getDenominatorPrimeFactors();

            // Pick the side with the least factors to be the base list for comparison
            IntFactorList *compareBaseList = (numeratorFactorList->getSize() <= numeratorFactorList->getSize())
                    ? numeratorFactorList
                    : denominatorFactorList;

            // The other side is the target list
            IntFactorList *compareTargetList = (compareBaseList == numeratorFactorList)
                    ? denominatorFactorList
                    : numeratorFactorList;

            // Preparing to loop through compareBaseList and cancel common factors
            // between compareBaseList and compareTargetList
            IntFactorListNode* currentNode = compareBaseList->getHead();
            IntFactor* factorFromBaseList;

            for (currentNode; currentNode != nullptr; currentNode = currentNode->front) {
                factorFromBaseList = currentNode->factor;

                // cancelWithFactor has side effects that also affect factorFromBaseList
                compareTargetList->cancelWithFactor( factorFromBaseList );

            }

            numerator = numeratorFactorList->getValue();
            denominator = denominatorFactorList->getValue();

            delete numeratorFactorList;
            delete denominatorFactorList;
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
