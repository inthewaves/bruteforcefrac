/*  IntFactorList.h
 *  This file is a part of the bruteforcefrac library.
 *
 *  Copyright (c) 2019 Paul Ngo
 *
 *  Licensed under the MIT License
 */

#ifndef BRUTEFORCEFRAC_INTFACTORLIST_H
#define BRUTEFORCEFRAC_INTFACTORLIST_H

#include "IntFactor.h"
#include "IntFactorListNode.h"
#include "PrimeFactorFinder.h"

#include <cstdio>
#include <cmath>

#include <cstdint>
#include <cinttypes>

namespace bffrac {

/**
 * A a doubly-linked list containing IntFactors,
 * intended to be used with ascending-order prime factors.
 */
class IntFactorList {
private:

    /**
     * @brief Recursively creates a factor list for a positive int.
     *
     * The function recursively prime factorizes @p valToFactor, using the
     * append method to add recursively add prime factors onto the list
     *
     * @pre The list is empty, @p valToFactor is greater than 3
     * @param valToFactor - The value to prime factorize
     */
    void primeFactorizeRecurse(uint64_t valToFactor) {
        uint64_t primeFactor = getSmallestPrimeFactor(valToFactor);

        // Base step: If valToFactor is prime, append it and stop recursing
        if (valToFactor == primeFactor) {
            appendFactor(new IntFactor(primeFactor, 1));
            return;
        }

        // Else valToFactor is composite
        uint64_t otherFactor = valToFactor / primeFactor;

        appendFactor(new IntFactor(primeFactor, 1));

        // recursive step
        primeFactorizeRecurse(otherFactor);
    }

    IntFactorListNode* head;
    IntFactorListNode* tail;
    unsigned int size;

public:
    IntFactorList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~IntFactorList() {
        if (head) {
            IntFactorListNode *loopNode = head;

            if (head->front) {
                IntFactorListNode *nextNode;
                do {
                    nextNode = loopNode->front;
                    delete loopNode;
                    loopNode = nextNode;
                } while (loopNode);
            } else delete head;
        }
    }

    void print() {
        if (head) {
            IntFactorListNode *loopNode = head;

            while (loopNode) {
                printf("%" PRIu64"^%" PRIu64 " ", loopNode->factor->getBase(), loopNode->factor->getExponent());
                loopNode = loopNode->front;
            }
            printf("(Size: %u)\n", size);
        } else printf("empty IntFactorList\n");
    }

    unsigned int getSize() {return size;}

    IntFactorListNode* getHead() {return head;}

    /**
     * Multiplies all the factors in the list together.
     * @return The product of all the factors in the list.
     *         Empty lists are treated as 0.
     */
    uint64_t getValue() {
        if (size == 0) return 0;

        uint64_t returnValue = 1;
        if (head) {
            IntFactorListNode *loopNode = head;
            while (loopNode) {
                returnValue *= loopNode->factor->getValue();
                loopNode = loopNode->front;
            }
        }

        return returnValue;
    }

    /**
     * Appends a new factor to the end of the list.
     *
     * This works under the assumption that factors are added in ascending order
     * due to the way the factorization algorithm is implemented.
     *
     * @param newFactor - The factor to be appended
     */
    void appendFactor(IntFactor* newFactor) {
        if (newFactor) {
            // Don't append factors that have bases of 1 or 0, unless it's an empty list
            if (newFactor->getBase() > 1 || size == 0) {
                // Check if list is nonempty
                if (tail) {
                    // If the tail base matches with the factor to be appended,
                    // just bump the tail's exponent. Otherwise add new node.
                    if (tail->factor->getBase() == newFactor->getBase()) {
                        tail->factor->setExponent(tail->factor->getExponent() + newFactor->getExponent());
                        // we don't use it anymore, so stop memory leaks
                        delete newFactor;
                    } else {
                        auto newNode = new IntFactorListNode(newFactor);
                        newNode->back = tail;
                        tail->front = newNode;
                        tail = newNode;
                        size++;
                    }
                } else {
                    // Here, list is empty
                    tail = new IntFactorListNode(newFactor);
                    head = tail;
                    size++;
                }
            }
            else delete newFactor;
        }

    }

    IntFactorListNode* findNodeWithBase(uint64_t base) {
        IntFactorListNode *loopNode = head;

        while (loopNode) {
            if (loopNode->factor->getBase() == base) break;
            loopNode = loopNode->front;
        }

        return loopNode;
    }

    /**
     * Delete a node from the IntFactorList.
     *
     * @pre nodeToRemove is a part of the IntFactorList
     * @param nodeToRemove - A node inside IntFactorList that is to be removed.
     */
    void deleteNode(IntFactorListNode* nodeToRemove) {
        // make sure we're removing valid node and list is non empty
        if (nodeToRemove && head) {
            // deleting an intermediate node results in nodes with links that need to be fixed
            IntFactorListNode* nodeToFixBack;
            IntFactorListNode* nodeToFixFront;

            if (nodeToRemove == head && nodeToRemove == tail) {
                // case: this is a single-element list
                head = nullptr;
                tail = nullptr;
            } else if (nodeToRemove == head) {
                // case: trying to remove head
                nodeToFixFront = nodeToRemove->front;
                nodeToFixFront->back = nullptr;
                head = nodeToFixFront;
            } else if (nodeToRemove == tail) {
                // case: trying to remove tail
                nodeToFixBack = nodeToRemove->back;
                nodeToFixBack->front = nullptr;
                tail = nodeToFixBack;
            } else {
                // case: removing an intermediate node
                nodeToFixFront = nodeToRemove->front;
                nodeToFixBack = nodeToRemove->back;
                nodeToFixBack->front = nodeToFixFront;
                nodeToFixFront->back = nodeToFixBack;
            }

            delete nodeToRemove;
            size--;
        }
    }

    /**
     * Performs a 'cancellation' with the list.
     *
     * That is, divisor factor is put under all the factors and cancel with what can be canceled.
     *
     * For example, suppsoe we have list of [3^1, 5^3, 7^5], and suppose
     * - x == 5^4, so cancelWithFactor(x) turns the list into [3^1, 7^5],
     *      and by side effects, x is turned into x == 5^1
     * - x == 5^1, so cancelWithFactor(x) turns the list into [3^1, 5^2, 7^5]
     *      and x is turned into x == 5^0
     * - x == 5^3, so cancelWithFactor(x) turns the list into [3^1, 7^5]
     *      and x is turned into x == 5^0
     *
     * @pre Both this IntFactorList and divisorFactor are made up of prime factors.
     * @param divisorFactor - The divisor factor we want to cancel with.
     *                        This method has side effects on this divisor:
     *                        it will also cause a cancellation effect
     */
    void cancelWithFactor(IntFactor* divisorFactor) {
        if (divisorFactor) {
            IntFactorListNode* commonFactorNode = findNodeWithBase(divisorFactor->getBase());
            if (commonFactorNode) {

                IntFactor* commonFactor = commonFactorNode->factor;

                uint64_t smallerExponent = (commonFactor->getExponent() <= divisorFactor->getExponent())
                        ? commonFactor->getExponent()
                        : divisorFactor->getExponent();

                commonFactor->setExponent(commonFactor->getExponent() - smallerExponent);

                // side effect
                divisorFactor->setExponent(divisorFactor->getExponent() - smallerExponent);
            }
        }
    }

    /**
     * Replaces the list with the prime factorization of @p valToFactor.
     *
     * Basically a wrapper method for the recursion.
     * The list contains the canonical form of the positive
     * integer @p valToFactor. For example, 60 = 2^2 * 3 * 5 is
     * the canonical form of 60, so primeFactorize(60) creates
     * an IntFactorList with elements [2^2, 3, 5].
     *
     * @param valToFactor - The value to prime factorize
     */
    void primeFactorize(uint64_t valToFactor) {
        // Delete the entire list first
        while (size > 0) {
            deleteNode(head);
        }

        // Numbers less than or equal to 3 don't need to be factored
        if (valToFactor <= 3)
            appendFactor(new IntFactor(valToFactor, 1));
        else
            primeFactorizeRecurse(valToFactor);
    }
};

} //namespace bffrac

#endif //BRUTEFORCEFRAC_INTFACTORLIST_H
