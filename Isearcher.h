//
// Created by oryakov on 1/7/19.
//

#ifndef MILESTONE2_ISEARCHER_H
#define MILESTONE2_ISEARCHER_H

#include <iostream>
#include "Searchable.h"
using namespace std;

template <class T, class Solution>
class Isearcher {
public:
    virtual Solution search(Searchable<T>* searchable) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
};


#endif //MILESTONE2_ISEARCHER_H
