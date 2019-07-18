#include <cmath>
#include <cstdio>

#include <cstdint>
#include <cinttypes>

#include "IntFactorTree/IntFactorTree.h"
#include "IntFactorList/IntFactorList.h"

int main(int argc, char** argv) {
    if (argc >= 2) {
	    uint64_t factorme = 0;
        if (sscanf(argv[1], "%" PRIu64, &factorme) == 1) {
            bruteforcefrac::IntFactorList factorList = bruteforcefrac::IntFactorList();
            factorList.primeFactorize(factorme);
            factorList.print();
        }
    }

}

