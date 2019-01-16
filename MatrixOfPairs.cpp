//
// Created by oryakov on 1/13/19.
//

#include "MatrixOfPairs.h"

MatrixOfPairs::MatrixOfPairs(const vector<State<pair<int, int>> *> &allStates,
                             State<pair<int, int>> *initialState,
                             State<pair<int, int>> *goalState,
                             const map<State<pair<int, int>> *, vector<State<pair<int, int>> *>> &stateAndValidNeighborsMap)
        : allStates(allStates), initialState(initialState),
          goalState(goalState),
          stateAndValidNeighborsMap(stateAndValidNeighborsMap) {}

State<pair<int, int>> *MatrixOfPairs::getInitialState() {
    return initialState;
}

State<pair<int, int>> *MatrixOfPairs::getGoalState() {
    return goalState;
}

vector<State<pair<int, int>> *>
MatrixOfPairs::getAllPossibleStates(State<pair<int, int>> *state) {
    return stateAndValidNeighborsMap.at(state);
}

const vector<State<pair<int, int>> *> &MatrixOfPairs::getAllStates() const {
    return allStates;
}

void
MatrixOfPairs::setAllStates(const vector<State<pair<int, int>> *> &allStates) {
    MatrixOfPairs::allStates = allStates;
}

void MatrixOfPairs::setInitialState(State<pair<int, int>> *initialState) {
    MatrixOfPairs::initialState = initialState;
}

void MatrixOfPairs::setGoalState(State<pair<int, int>> *goalState) {
    MatrixOfPairs::goalState = goalState;
}

const map<State<pair<int, int>> *, vector<State<pair<int, int>> *>> &
MatrixOfPairs::getStateAndValidNeighborsMap() const {
    return stateAndValidNeighborsMap;
}

void MatrixOfPairs::setStateAndValidNeighborsMap(
        const map<State<pair<int, int>> *, vector<State<pair<int, int>> *>> &stateAndValidNeighborsMap) {
    MatrixOfPairs::stateAndValidNeighborsMap = stateAndValidNeighborsMap;
}
