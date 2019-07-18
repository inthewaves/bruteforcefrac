/*  IntFactorVector.h
 *  This file is a part of the bruteforcefrac library.
 *
 *  Copyright (c) 2019 Paul Ngo
 *
 *  Licensed under the MIT License
 */


/**
 * A wrapper header for handing vectors of IntFactors
 */
#ifndef BRUTEFORCEFRAC_INTFACTORVECTOR_H
#define BRUTEFORCEFRAC_INTFACTORVECTOR_H

#include "IntFactor.h"
#include "PrimeFactorFinder.h"

#include <cstdint>

#include <vector>
using std::vector;

namespace bruteforcefrac {

    /**
     * Finds the index of a factor with a base of @p baseToFind
     *
     * @param facvec - The pointer of a vector<IntFactor*> to search.
     * @param baseToFind - The base we are looking for inside @p facvec.
     * @return The index of the first factor with a base of @p baseToFind,
     *          or -1 if not found.
     */
    unsigned long findIndexOfFactorWithBase(vector<IntFactor*>* facvec, uint64_t baseToFind) {
        // reference vector, not a copy
        vector<IntFactor*>& refVec = *facvec;

        for (unsigned long i = 0; i < facvec->size(); i++) {
            if (refVec[i]->getBase() == baseToFind) return i;
        }
        return -1;
    }

    /**
     * Performs a 'cancellation' with the vector.
     *
     * That is, divisor factor is put under all the factors and cancels with what
     * can be canceled.
     *
     * For example, suppose we have list of [3^1, 5^3, 7^5]. This list is the "numerator".
     * Now suppose that
     * - x == 5^4, so cancelWithFactor(x) turns the list into [3^1, 5^0, 7^5],
     *      and by side effects, x is turned into x == 5^1.
     *      This is because (3 * 5^3 * 7^5) / (5^4) = (3 * 7^5) / (5).
     * - x == 5^1, so cancelWithFactor(x) turns the list into [3^1, 5^0, 7^5]
     *      and x is turned into x == 5^0
     * - x == 5^3, so cancelWithFactor(x) turns the list into [3^1, 5^0, 7^5]
     *      and x is turned into x == 5^0
     *
     * @pre Both @p facvec and @p divisor are made up of prime factors, and @p facvec
     *      is in canonical form (e.g. 3^3 * 5 and not 3 * 3^2 * 5 or 3 * 3 * 3 * 5).
     * @param facvec -  A vector<IntFactor> of prime factors we want to cancel against
     *                  (i.e. the "numerator")
     * @param divisor - The divisor factor we want to cancel with.
     *                  (i.e. the "denominator")
     *                  This method has side effects on this divisor:
     *                  it will also cause a cancellation effect on it
     */
    void cancelFacVecWithFactor(vector<IntFactor*>* facvec, IntFactor* divisor) {
        if (divisor && facvec && !facvec->empty()) {
            unsigned long indexOfCommonFactor = findIndexOfFactorWithBase(facvec, divisor->getBase());
            if (indexOfCommonFactor >= 0) {
                IntFactor* commonFactor = (*facvec)[indexOfCommonFactor];

                uint64_t smallerExponent = (commonFactor->getExponent() <= divisor->getExponent())
                                           ? commonFactor->getExponent()
                                           : divisor->getExponent();

                commonFactor->setExponent(commonFactor->getExponent() - smallerExponent);

                // side effect
                divisor->setExponent(divisor->getExponent() - smallerExponent);
            }
        }
    }

    /**
     * Pushes an IntFactor to a pointer to a vector<IntFactor*>.
     *
     * This function pushes IntFactors with base of @p baseToPush and an exponent
     * of 1. If the IntFactor at the tail of @p facvec has the same base @p baseToPush,
     * then the exponent at the tail element will be increased by 1. In essence,
     * this function is like multiplying by (@p baseToPush)^1 to a product.
     *
     * @example factor_push_back([3,5^2], 5) results in [3,5^2] turning into
     * [3,5^3] because (3 * 5^2) * 5^1 = 3 * 5^3.
     *
     * @note We assume that the exponent is 1. Currently we don't have any need
     * to push with other exponents, so this assumption means we can possibly save
     * mem by just passing a uint64_t instead of an IntFactor as a parameter.
     *
     * @param facvec - The pointer to a vector<IntFactor*> to push to.
     * @param baseToPush - The base to push into the vector.
     */
    void factor_push_back(vector<IntFactor*>* facvec, uint64_t baseToPush) {
        if (facvec) {
            if (facvec->empty()) {
                facvec->push_back(new IntFactor(baseToPush,1));
            } else {
                // If the base at the tail is the same as the base of fac,
                // just bump the exponent by 1, since a^b * a^1 = a^(b+1).
                IntFactor* factorAtTail = (*facvec)[facvec->size()-1];
                if (factorAtTail->getBase() == baseToPush) {
                    factorAtTail->setExponent(factorAtTail->getExponent() + 1);
                } else {
                    facvec->push_back(new IntFactor(baseToPush,1));
                }
            }
        }
    }

    /**
     * Creates a vector of prime IntFactors.
     * @param valToFactor - The positive integer to factor into prime factors
     * @return A pointer to a vector<IntFactor*>
     */
    vector<IntFactor*>* primeFactorizeToVector(uint64_t valToFactor) {
        vector<IntFactor*>* vecOfPrimes = new vector<IntFactor*>;

        // Don't bother trying to factor numbers less than 3
        if (valToFactor <= 3) {
            factor_push_back(vecOfPrimes, valToFactor);
        } else {
            // Perform trial division
            while (valToFactor > 1) {
                uint64_t primeFactor = getSmallestPrimeFactor(valToFactor);

                // if valToFactor is already prime, append it and stop looping
                // otherwise, factor valToFactor, append the prime factor, and keep
                // factoring
                if (valToFactor == primeFactor) {
                    factor_push_back(vecOfPrimes, valToFactor);
                    break;
                } else {
                    valToFactor /= primeFactor;
                    factor_push_back(vecOfPrimes, primeFactor);
                }
            }

        }

        return vecOfPrimes;
    }

    /**
     * Returns the product of all the in a vector<IntFactor*>.
     * @param facvec - The pointer to a vector<IntFactor*> to get the value of.
     * @return The product of all the factors.
     *         Returns -1 if @p facvec is null.
     *         Returns 0 if @p facvec is empty.
     *
     */
    uint64_t getValue(vector<IntFactor*>* facvec) {
        uint64_t returnVal = -1;
        if (facvec) {
            if (facvec->empty()) return 0;

            returnVal = 1;
            for (unsigned long i = 0; i<facvec->size(); i++) {
                returnVal *= (*facvec)[i]->getValue();
            }
        }
        return returnVal;
    }

}

#endif //BRUTEFORCEFRAC_INTFACTORVECTOR_H
