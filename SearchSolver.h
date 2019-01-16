//
// Created by oryakov on 1/16/19.
//

#ifndef MILESTONE2_SEARCHSOLVER_H
#define MILESTONE2_SEARCHSOLVER_H

#include "Solver.h"
#include "Isearcher.h"
template <class Problem, class Solution, class T>
class SearchSolver : public Solver<Problem, Solution> {
    Isearcher<T, Solution>* iSearcher;
public:
    SearchSolver(Isearcher<T, Solution> *iSearcher) : iSearcher(
            iSearcher) {}

    Solution solve(Problem problem) override {
        return iSearcher->search(problem);
    }
};


#endif //MILESTONE2_SEARCHSOLVER_H
