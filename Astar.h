//
// Created by oryakov on 1/14/19.
//

#ifndef MILESTONE2_ASTAR_H
#define MILESTONE2_ASTAR_H

#include "Searcher.h"
#include <set>
#include "State.h"
#include <algorithm>
#include <unordered_set>
#include <math.h>


template<class T, class Solution>
class Astar : public Searcher<T, Solution> {

    unordered_set<State<T> *> closed;

public:

    static double distFunction(State<pair<int, int>> *s, State<pair<int, int>> *goal) {
            int sX = s->getState().first;
            int sY = s->getState().second;
            int goalX = goal->getState().first;
            int goalY = goal->getState().second;
            double distanceX = pow(sX - goalX, 2);
            double distanceY = pow(sY - goalY, 2);
            double calcDistance = sqrt(distanceX + distanceY);
            return calcDistance;
    }

//    void setDistFunction(double distFunction1) {
//        Astar::distFunction = distFunction1;
//    }

//    double g(State<T> *s, State<T> *n) {
//        return (n->getTotalCost() + s->getCost());
//    }

    template<class function>
    static double h(State<T> *s, State<T> *goal, function distFunction) {
        double dist = distFunction(s, goal);
        return dist;
    }

    Solution search(Searchable<T> *searchable) override {
        typename unordered_set<State<T>*>::iterator itClosed;

        static State<T>* goalState = searchable->getGoalState();
        State<T>* n;
        vector<State<T>*> curPossibleStates;
        vector<State<T>*> resPath;

        class LessThanOfStateCostPlusDist
        {
        public:
            bool operator()(State<T>* a, State<T>* b)
            {
                double uristA = h(a, goalState, distFunction);
                double uristB = h(b, goalState, distFunction);
                return (a->getTotalCost() + uristA) > (b->getTotalCost() + uristB);
            }
        };

        priority_queue<State<T>*, vector<State<T>*>, LessThanOfStateCostPlusDist> openList;
        priority_queue<State<T>*, vector<State<T>*>, LessThanOfStateCostPlusDist> openListCopy;



        openList.push(searchable->getInitialState());
        while (!openList.empty()) {
            n = openList.top();
            openList.pop();
            this->evaluatedNodes++;
            closed.insert(n);
            if (n == goalState) {
                //backtrace path to n (through recorded parents) and return path
                string strPath;
                resPath.push_back(n);
                while (n->getCameFrom() != nullptr) {
                    State<T>* temp = n->getCameFrom();
                    resPath.push_back(temp);
                    n = temp;
                }
                reverse(resPath.begin(), resPath.end());
                int resPathSize = (int) resPath.size();
                for (int a = 0; a < resPathSize; ++a) {
                    strPath += resPath[a]->findDirection(resPath[a], resPath[a]->directionOfPairs);
                    if ((a != (resPathSize -1)) && (a != 0)) {
                        strPath += ", ";
                    }
                }
                return strPath;
            }
            //Create n's successors
            curPossibleStates = searchable->getAllPossibleStates(n);
            if (curPossibleStates.empty()) {
                continue;
            }
            //For each successor s:

            int possibleStatesSize = (int) curPossibleStates.size();
            for (int l = 0; l< possibleStatesSize; ++l) {
                State<T>* s = curPossibleStates[l];

                // look for s in the openList queue
                itClosed = closed.find(s);
                if (itClosed != closed.end()) {
                    continue;
                }
                openListCopy = openList;
                bool foundInOpen = false;
                while (!openListCopy.empty()) {
                    State<T>* temp = openListCopy.top();
                    openListCopy.pop();
                    if (temp == s) {
                        foundInOpen = true;
                    }
                }
                //If s is not in CLOSED and s is not in OPEN:
                if ((itClosed == closed.end()) && (!foundInOpen)) {
                    //update that we came to s from n
                    s->setCameFrom(n);

                    //add(s,OPEN)
                    openList.push(s);
                } else {
                    //if this new path is better than previous one
                    if ((n->getTotalCost() + s->getCost()) < s->getTotalCost()) {
                        //If it is not in OPEN add it to OPEN
                        if (!foundInOpen) {
                            openList.push(s);
                        } else {
                            //Otherwise, adjust its priority in OPEN
                            s->setCameFrom(n);
                            double newTotalCost = (n->getTotalCost() + s->getCost());
                            s->setTotalCost(newTotalCost);
                            State<T>* temp = s;
                            // todo pop just s
                            //this->openList.pop();
                            // pop s:
                            vector<State<T>*> tempQ;
                            int i=0;
                            State<T>* state;
                            int openSize = (int) openList.size();
                            while(i < openSize)
                            {
                                if (openList.top() == s) {
                                    break;
                                }
                                tempQ.push_back(openList.top());
                                openList.pop();
                                ++i;
                            }
                            openList.pop(); //pop the requested 's'
                            int tempQsize = (int) tempQ.size();
                            for (int m = 0;  m < tempQsize; ++m) {
                                openList.push(tempQ[m]);
                            }
                            // push the new 's'
                            openList.push(temp);
                        }
                    }
                }
            }
        }
    }
};


#endif //MILESTONE2_ASTAR_H
