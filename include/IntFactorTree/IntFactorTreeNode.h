/*  IntFactorTreeNode.h
 *  This file is a part of the bruteforcefrac library.
 *
 *  Copyright (c) 2019 Paul Ngo
 *
 *  Licensed under the MIT License
 */

#ifndef BRUTEFORCEFRAC_INTFACTORTREENODE_H
#define BRUTEFORCEFRAC_INTFACTORTREENODE_H

#include <cmath>
#include <cstdio>

#include <cstdint>
// only needed for < C++11
// #define __STDC_FORMAT_MACROS
#include <cinttypes>

#include "IntFactor.h"
#include "PrimeFactorFinder.h"

namespace bffrac {

class IntFactorTreeNode {
private:
    IntFactor* factor;
    IntFactorTreeNode* leftNode;
    IntFactorTreeNode* rightNode;

    /**
     * Recursively prints out the leaves of an IntFactorTree.
     *
     * For public use, use the printTreeLeaves method instead.
     * @param x - The tree to print out
     */
    void printTreeLeaves_recurse(IntFactorTreeNode* x) {
        if (x == nullptr) return;

        printTreeLeaves_recurse(x->leftNode);

        // Only print if the left and right nodes are null
        // that is, only print if it is a leaf
        if (x->leftNode == nullptr && x->rightNode == nullptr)
            // PRIu64 is format string for uint64_t
            printf("%" PRIu64 "^%" PRIu64 " ", x->factor->getBase(), x->factor->getExponent());

        printTreeLeaves_recurse(x->rightNode);
    }

public:
    IntFactorTreeNode (IntFactor* factor) {
        this->factor = factor;
        leftNode = nullptr;
        rightNode = nullptr;
    }

    ~IntFactorTreeNode() {
        delete factor;
    }

    IntFactor* getFactor() {return factor;}

    IntFactorTreeNode* getLeftNode() {return leftNode;}

    IntFactorTreeNode* getRightNode() {return rightNode;}

    void setLeftNode(IntFactorTreeNode* leftNode) {this->leftNode = leftNode;}

    void setRightNode(IntFactorTreeNode* rightNode) {this->rightNode = rightNode;}

    /**
     * @brief Recursively creates a factor tree for a positive int.
     *
     * The function recursively prime factorizes an IntFactor containing a positive
     * int, returning the root of the prime factor tree. The prime factorization
     * method is a brute-force trial division.
     *
     * @param fac - A IntFactor containing a positive integer to be factorized.
     * @return An IntFactorTreeNode that is the root of the factor tree of \p fac.
     */
    IntFactorTreeNode* primeFactorize(IntFactor* fac) {
        //  newNode is the root of the prime factor tree for \p fac
        auto newNode = new IntFactorTreeNode(fac);
        uint64_t valToFac = newNode->factor->getValue();

        //  Don't try to factor one, zero, or anything negative
        if (valToFac <= 1) return newNode;

        uint64_t primeFactor = getSmallestPrimeFactor(valToFac);

        //  If valToFac is already prime,
        //  then the node is prime
        if (primeFactor == valToFac) {
            return newNode;
        }

        //  Otherwise, valToFac is composite
        auto primeFactorOfFac = new IntFactor(primeFactor, 1);
        auto otherFactorOfFac = new IntFactor(valToFac / primeFactor, 1);

        newNode->leftNode = new IntFactorTreeNode(primeFactorOfFac);

        //  recursive step
        newNode->rightNode = primeFactorize(otherFactorOfFac);

        return newNode;
    }

    /**
     * Prints out the tree leaves recursively.
     */
    void printTreeLeaves() {
        printTreeLeaves_recurse(this);
        printf("\n");
    }
};

} //namespace bffrac

#endif //BRUTEFORCEFRAC_INTFACTORTREENODE_H
