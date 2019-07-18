/*  PrimeFactorization.h
 *  This file is a part of the bruteforcefrac library.
 *
 *  Copyright (c) 2019 Paul Ngo
 *
 *  Licensed under the MIT License
 */

#ifndef BRUTEFORCEFRAC_PRIMEFACTORFINDER_H
#define BRUTEFORCEFRAC_PRIMEFACTORFINDER_H

#include <cmath>

#include <cstdint>
#include <cinttypes>

namespace bruteforcefrac {

/**
 * @brief Returns the smallest prime factor of the param.
 *
 * This is a brute-force trial division algorithm for finding the
 * smallest prime factor.
 *
 * @param valToFactor - The value to prime factorize.
 * @return The smallest prime factor of valToFactor
 *          (which is \p valToFactor if it is prime).
 */
uint64_t getSmallestPrimeFactor(uint64_t valToFactor) {
    //  if valToFac is a composite integer then it has a prime divisor <= sqrt(valToFac)
    uint64_t stoppingValue = (uint64_t) floor(sqrt(valToFactor));

    //  Even numbers are clearly not prime
    if (valToFactor % 2 == 0) return 2;

    //  Brute force: check each odd integer to see if it is divisible
    //  At this point, it's not even so we ignore all even test values
    for (uint64_t currentDivisor = 3; currentDivisor <= stoppingValue; currentDivisor += 2) {
        if (valToFactor % currentDivisor == 0) return currentDivisor;
    }

    //  If we reached the end of the loop, valToFactor is prime
    //  so we return valToFactor
    return valToFactor;
}

} //namespace bruteforcefrac

#endif //BRUTEFORCEFRAC_PRIMEFACTORFINDER_H
