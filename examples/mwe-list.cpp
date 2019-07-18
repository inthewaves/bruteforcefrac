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
            bffrac::IntFactorList factorList = bffrac::IntFactorList();
            factorList.primeFactorize(factorme);
            factorList.print();
        }
    }

}

