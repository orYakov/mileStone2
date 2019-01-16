//
// Created by oryakov on 1/9/19.
//

#ifndef MILESTONE2_MATRIXOFSTATES_H
#define MILESTONE2_MATRIXOFSTATES_H

#include "State.h"
#include "Searchable.h"
#include <map>
#include <list>
using  namespace std;
template <class T>
class MatrixOfStates : public Searchable<T> {
    list<State<T>*> allStates;
    State<T>* initialState;
    State<T>* goalState;

//    struct cmpByState {
//        bool operator()(State<T>* a, State<T>* b) {
//            return a->getState() < b->getState();
//        }
//    };
//
//     typename std::map <State<T>*, list<State<T>*>, cmpByState>::map stateAndValidNeighborsMap;

    struct cmpByState {
        bool operator()(State<T>* a, State<T>* b) {
            return a->getState() < b->getState();
        }
    };

    typedef map<State<T>*, list<State<T>*>, cmpByState> stateAndValidNeighborsMap;
    stateAndValidNeighborsMap myMap;

public:
    MatrixOfStates(list<State<T> *> &allStates1, State<T> *initialState1,
                   State<T> *goalState1,
                   stateAndValidNeighborsMap& myMap1) {
        allStates = allStates1;
        initialState = initialState1;
        goalState = goalState1;
        myMap = myMap1;
    }

    virtual State<T>* getInitialState() {
        return initialState;
    }

    virtual State<T>* getGoalState() {
        return goalState;
    }

    virtual list<State<T>*> getAllPossibleStates(State<T>* state) {
        if (myMap.count(state)) {
            list<State<T>*> res = myMap[state];
            return res;
        } else {
            return list<State<T>*>();
        }
    }

    const list<State<T> *> &getAllStates() const {
        return allStates;
    }

    void setAllStates(const list<State<T> *> &allStates) {
        MatrixOfStates::allStates = allStates;
    }

    void setInitialState(State<T> *initialState) {
        MatrixOfStates::initialState = initialState;
    }

    void setGoalState(State<T> *goalState) {
        MatrixOfStates::goalState = goalState;
    }

    map<State<T> *, list<State<T> *>> &
    getStateAndValidNeighborsMap() {
        return this->stateAndValidNeighborsMap;
    }

    void setStateAndValidNeighborsMap(map<State<T> *, list<State<T> *>> &stateAndValidNeighborsMap1) {
        this->stateAndValidNeighborsMap = stateAndValidNeighborsMap1;
    }
};


#endif //MILESTONE2_MATRIXOFSTATES_H
