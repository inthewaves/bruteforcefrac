#include "IntFactor.h"
#include "IntFactorVector.h"
#include "RationalNum.h"

#include <cmath>
#include <cstdio>

#include <cstdint>
#include <cinttypes>

int main(int argc, char** argv) {
    if (argc >= 2) {
	    uint64_t factorme = 0;
        if (sscanf(argv[1], "%" PRIu64, &factorme) == 1) {
	        printf("Prime factorizing %" PRIu64 " with vectors:\n", factorme);
	        std::vector<bruteforcefrac::IntFactor*>* primeFactors = bruteforcefrac::primeFactorizeToVector(factorme);
            bruteforcefrac::printFacVec(primeFactors);
        }
    }

}

