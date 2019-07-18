# bruteforcefrac
This is a header-only C++ library for simplifying rational numbers using brute-force prime 
factorization. The motivation for this project is to refresh myself on data structures and 
to lay a foundation for a matrix row operations program.

The program contains two data structures implementing prime factorization. These data
structures were created for review purposes.

## Using the library
### Minimal working example 
Put all the header files in [`include`](include/) directory into 
one place, and make a `mwe.cpp` file  (or copy it from the [`examples/`](examples/) directory) with the following code:

```c++
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

```

A compilation and a test run are as follows:

```console
$ g++ mwe.cpp && ./a.out
What do you want to factor? >>> 5435345354
Prime factorizing 5435345354 with tree:
2^1 2609^1 1041653^1 
Prime factorizing 5435345354 with list:
2^1 2609^1 1041653^1 (Size: 3)

Enter a fraction in the form a/b >>> 1480/23456
testFrac: 1480/23456
simplified testFrac: 185/2932
```

### Speed
For normal usage with relatively small numbers, the factoring and simplification works 
fine on modern home computers.

But take the prime number 12764787846358441471. With the `mwe-list.cpp` and `mwe-tree.cpp` 
files (found under the [examples/](examples/) directory), we have the following with 
the `time` command:
```console
$ g++ -Wall -O3 mwe-tree.cpp -o mwe-tree 
$ g++ -Wall -O3 mwe-list.cpp -o mwe-list 
$ time ./mwe-tree 12764787846358441471
Prime factorizing 12764787846358441471 with tree:
12764787846358441471^1 

real    0m15.028s
user    0m15.027s
sys     0m0.000s
$ time ./mwe-list 12764787846358441471
12764787846358441471^1 (Size: 1)

real    0m15.942s
user    0m15.938s
sys     0m0.000s
```

## License
Licensed under the MIT License. See [LICENSE.md](LICENSE.md) for details.
