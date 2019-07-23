#include "bruteforcefrac.h"

#include <cmath>
#include <cstdio>

#include <cstdint>
#include <cinttypes>


int main() {
    printf("What do you want to factor? >>> ");

    uint64_t factorme = 0;
    scanf("%" PRIu64, &factorme);

    // "IntFactorVector.h"
    std::vector<bffrac::IntFactor*>* primeFactors = bffrac::primeFactorizeToVector(factorme);
    bffrac::printFacVec(primeFactors);
    delete primeFactors;

    // "RationalNum.h"
    int64_t numer = 0; int64_t denom = 0;
    printf("\nEnter a fraction in the form a/b >>> ");
    if (scanf("%" PRIi64 "/%" PRIi64, &numer, &denom) == 2) {
        bffrac::RationalNum testFrac = bffrac::RationalNum(numer,denom);

        printf("testFrac: %" PRIu64 "/%" PRIu64 "\n", testFrac.getNumerator(), testFrac.getDenominator() );
        testFrac.simplify();
        printf("simplified testFrac: %" PRIu64 "/%" PRIu64 "\n", testFrac.getNumerator(),
               testFrac.getDenominator() );
    }
}
