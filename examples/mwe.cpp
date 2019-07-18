#include <cmath>
#include <cstdio>

#include <cstdint>
#include <cinttypes>

#include "bruteforcefrac.h"

int main() {
    printf("What do you want to factor? >>> ");

    uint64_t factorme = 0;
    scanf("%" PRIu64, &factorme);

    // "IntFactorTree.h"
    bruteforcefrac::IntFactorTree userTree = bruteforcefrac::IntFactorTree(factorme);
    printf("Prime factorizing %" PRIu64 " with tree:\n", factorme);
    userTree.primeFactorize();
    userTree.printLeaves();

    // "IntFactorList.h"
    bruteforcefrac::IntFactorList factorList = bruteforcefrac::IntFactorList();
    factorList.primeFactorize(factorme);
    printf("Prime factorizing %" PRIu64 " with list:\n", factorme);
    factorList.print();

    // "RationalNum.h"
    int64_t numer = 0; int64_t denom = 0;
    printf("\nEnter a fraction in the form a/b >>> ");
    if (scanf("%" PRIi64 "/%" PRIi64, &numer, &denom) == 2) {
        bruteforcefrac::RationalNum testFrac = bruteforcefrac::RationalNum(numer,denom);

        printf("testFrac: %" PRIu64 "/%" PRIu64 "\n", testFrac.getNumeratorValue(), testFrac.getDenominatorValue() );
        testFrac.simplify();
        printf("simplified testFrac: %" PRIu64 "/%" PRIu64 "\n", testFrac.getNumeratorValue(), testFrac.getDenominatorValue() );
    }
}
