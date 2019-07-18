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
            bffrac::IntFactorTree userTree = bffrac::IntFactorTree(factorme);
	        printf("Prime factorizing %" PRIu64 " with tree:\n", factorme);
	        userTree.primeFactorize();
	        userTree.printLeaves();
        }
    }

}

