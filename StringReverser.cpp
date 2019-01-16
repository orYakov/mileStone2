//
// Created by oryakov on 1/7/19.
//

#include "StringReverser.h"
#include <algorithm>


string StringReverser::solve(string problem) {
    reverse(problem.begin(), problem.end());
    return problem;
}
