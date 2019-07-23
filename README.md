# bruteforcefrac
This is a header-only C++17 library for a rational number class. The motivation for this project 
is to refresh myself on data structures and to lay a foundation for a matrix row operations program.

The library uses vectors to hold prime factors and also functions to factor a positive integer
into its canonical form. The prime factors will be returned as a vector of IntFactors, another
class in this library.

The library also contains two unused data structures implementing recursive prime factorization 
(IntFactorList and IntFactorTree). These data structures were created for review purposes.

## Using the library
### Unit tests
The unit tests directory, [`tests/`](tests/), contains examples of using this library. For
instance, examples of RationalNum usage are located in 
[`tests/test_rationalnum.cpp`](tests/test_rationalnum.cpp), including simplification, addition,
subtraction, multiplication, and division.

### Minimal working example 
Put all the header files in [`include/`](include/) directory into one place, and make a `mwe.cpp` 
file  (or copy it from the [`examples/`](examples/) directory) with the following code:

```c++
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

        printf("testFrac: %" PRIu64 "/%" PRIu64 "\n", testFrac.getNumerator(), testFrac.getDenominator());
        testFrac.simplify();
        printf("simplified testFrac: %" PRIu64 "/%" PRIu64 "\n", testFrac.getNumerator(),
                testFrac.getDenominator() );
    }
}
```

A compilation and a test run is as follows:

```console
$ g++ mwe.cpp && ./a.out
What do you want to factor? >>> 5435345354
2^1 * 2609^1 * 1041653^1
Enter a fraction in the form a/b >>> 1480/23456
testFrac: 1480/23456
simplified testFrac: 185/2932
```

### Speed
Prime factorization is done with trial division. For normal usage with relatively small numbers, the 
factoring and rational number simplification works fast on modern home computers.

Take the prime number 12764787846358441471. Using the old implementations from the `mwe-list.cpp` and 
`mwe-tree.cpp` files (found under the [`examples/`](examples/) directory), we have the following with 
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
