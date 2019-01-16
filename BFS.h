//
// Created by oryakov on 1/14/19.
//

#ifndef MILESTONE2_BFS_H
#define MILESTONE2_BFS_H

#include "State.h"
#include "Searcher.h"

template <class T, class Solution>
class BFS : public Searcher<T, Solution> {

public:
    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }

    Solution search(Searchable<T> *searchable) override {
        State<T>* goalState = searchable->getGoalState();
        State<T>* initialState = searchable->getInitialState();

        // Create a queue for BFS
        list<State<T>*> queue;



        // Mark the current node as visited and enqueue it
        initialState->setVisited(true);
        queue.push_back(initialState);


        while(!queue.empty())
        {
            // Dequeue a vertex from queue and print it
            State<T>* s = queue.front();
            cout << s->getCost() << " ";
            queue.pop_front();
            ++this->evaluatedNodes;
            if (s == goalState) {
                cout<<endl<<"total cost BFS: " << s->getTotalCost() << endl;
                cout<<"numOfNodes: "<<getNumberOfNodesEvaluated()<<endl;
                //backtrace path to n (through recorded parents) and return path
                vector<State<T> *> resPath;
                string strPath;
                State<T> *n = s;
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

            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            vector<State<T>*> curPossibleStates;
            curPossibleStates = searchable->getAllPossibleStates(s);
            int possibleStatesSize = (int) curPossibleStates.size();
            for (int i = 0; i < possibleStatesSize; ++i) {
                if (!(curPossibleStates[i]->isVisited())) {
                    curPossibleStates[i]->setCameFrom(s);
                    curPossibleStates[i]->setVisited(true);
                    queue.push_back(curPossibleStates[i]);
                }
            }
        }



    return "end of BFS";
    }
};


#endif //MILESTONE2_BFS_H
