/*  IntFactorListNode.h
 *  This file is a part of the bruteforcefrac library.
 *
 *  Copyright (c) 2019 Paul Ngo
 *
 *  Licensed under the MIT License
 */

#ifndef BRUTEFORCEFRAC_INTFACTORLISTNODE_H
#define BRUTEFORCEFRAC_INTFACTORLISTNODE_H

#include "IntFactor.h"

namespace bruteforcefrac {

/**
 * A node for a doubly-linked list containing IntFactors
 */
class IntFactorListNode {
public:
    IntFactorListNode(IntFactor* factor) {
        this->factor = factor;
        back = nullptr;
        front = nullptr;
    }

    ~IntFactorListNode() {
        if (factor) delete factor;
    }

    IntFactor* factor;
    IntFactorListNode* back;
    IntFactorListNode* front;

};

} //namespace bruteforcefrac

#endif //BRUTEFORCEFRAC_INTFACTORLISTNODE_H
