/*  IntFactor.h
 *  This file is a part of the bruteforcefrac library.
 *
 *  Copyright (c) 2019 Paul Ngo
 *
 *  Licensed under the MIT License
 */

#ifndef BRUTEFORCEFRAC_INTFACTOR_H
#define BRUTEFORCEFRAC_INTFACTOR_H

#include <cmath>
#include <cstdint>

namespace bffrac {

/**
 * An IntFactor is made up of a base and an exponent.
 *
 * The max base/exponent is UINT64_MAX
 * (2^64 -1 = 18446744073709551615 on my system)
 *
 */
    class IntFactor {
    private:
        uint64_t base;
        uint64_t exponent;
    public:
        IntFactor(uint64_t base, uint64_t exponent) {
            this->base = base;
            this->exponent = exponent;
        }

        uint64_t getBase() {return base;}

        uint64_t getExponent() {return exponent;}

        uint64_t getValue() {
            if (base == 0) return 0;
            if (exponent == 0) return 1;
            if (exponent == 1) return base;
            return (uint64_t)(pow(base,exponent));
        }

        void setExponent(uint64_t exponent) {this->exponent = exponent;}

        void setBase(uint64_t base) {this->base = base;}
    };

} //namespace bffrac

#endif //BRUTEFORCEFRAC_INTFACTOR_H
