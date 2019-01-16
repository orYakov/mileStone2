//
// Created by oryakov on 1/13/19.
//

#ifndef MILESTONE2_DFS_H
#define MILESTONE2_DFS_H

#include "State.h"
#include "Searcher.h"

template<class T, class Solution>
class DFS : public Searcher<T, Solution> {

public:
    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }

    Solution search(Searchable<T> *searchable) override {
        State<T> *goalState = searchable->getGoalState();
        State<T> *initialState = searchable->getInitialState();
        string strPath = DFSUtil(initialState, goalState, searchable);

        return strPath;
    }

    string DFSUtil(State<T> *initialState, State<T> *goalState,
                   Searchable<T> *searchable) {

        // Mark the current node as visited and
        // print it
        initialState->setVisited(true);
        ++this->evaluatedNodes;
        if (initialState == goalState) {
            cout << initialState->getCost() << endl;
            cout << "total cost DFS: " << initialState->getTotalCost() << endl;
            cout << "numOfNodes: " << getNumberOfNodesEvaluated() << endl;
            //backtrace path to n (through recorded parents) and return path
            vector<State<T> *> resPath;
            string strPath;
            State<T> *n = initialState;
            resPath.push_back(n);
            while (n->getCameFrom() != nullptr) {
                State<T> *temp = n->getCameFrom();
                resPath.push_back(temp);
                n = temp;
            }
            reverse(resPath.begin(), resPath.end());
            int resPathSize = (int) resPath.size();
            for (int a = 0; a < resPathSize; ++a) {
                strPath += resPath[a]->findDirection(resPath[a],
                                                     resPath[a]->directionOfPairs);
                if ((a != (resPathSize - 1)) && (a != 0)) {
                    strPath += ", ";
                }
            }
            return strPath;
        }
        cout << initialState->getCost() << " ";

        // Recur for all the vertices adjacent
        // to this vertex
        vector<State<T> *> curPossibleStates;
        curPossibleStates = searchable->getAllPossibleStates(initialState);
        int possibleStatesSize = (int) curPossibleStates.size();
        for (int i = 0; i < possibleStatesSize; ++i) {
            if (!(curPossibleStates[i]->isVisited())) {
                curPossibleStates[i]->setCameFrom(initialState);
                return DFSUtil(curPossibleStates[i], goalState, searchable);
            }
        }
    }

};


#endif //MILESTONE2_DFS_H
