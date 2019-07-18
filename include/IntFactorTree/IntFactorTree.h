/*  IntFactorTree.h
 *  This file is a part of the bruteforcefrac library.
 *
 *  Copyright (c) 2019 Paul Ngo
 *
 *  Licensed under the MIT License
 */

#ifndef BRUTEFORCEFRAC_INTFACTORTREE_H
#define BRUTEFORCEFRAC_INTFACTORTREE_H

#include "IntFactorTreeNode.h"

#include <cstdint>
#include <cinttypes>

namespace bffrac {

class IntFactorTree {
private:
    IntFactorTreeNode* root;

public:
    IntFactorTree(uint64_t rootValue) {
        root = new IntFactorTreeNode(new IntFactor(rootValue, 1));
    }

    ~IntFactorTree() {
        if (root) {
            deleteTree_recurse(root);
        }
    }

    IntFactorTreeNode* getRoot() {return root;}

    /**
     * Deletes tree nodes recursively.
     * @param x - The root of the tree to be deleted
     */
    void deleteTree_recurse(IntFactorTreeNode* x) {
        if (x) {
            deleteTree_recurse(x->getLeftNode());
            deleteTree_recurse(x->getRightNode());

            delete x;
        }
    }

    /**
     * Grows the factor tree
     *
     * This factorizes the positive integer stored in its root,
     * growing the tree with its factors.
     * The prime factors are at the leaves of the tree.
     *
     * @pre The tree is just a root.
     */
    void primeFactorize() {
        if (root) {
            root = root->primeFactorize(root->getFactor());
        }
    }

    void printLeaves() {
        if (root) {
            root->printTreeLeaves();
        }
    }

};

}

#endif //BRUTEFORCEFRAC_INTFACTORTREE_H
