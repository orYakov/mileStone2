//
// Created by oryakov on 1/9/19.
//
#define LINE_SEPARATOR "@"

#include <thread>
#include "IntPairMatrixCreator.h"
#include "MyTestClientHandler.h"
#include "BestFirstSearch.h"
#include "DFS.h"
#include "BFS.h"
#include "Astar.h"
#include "FileCasheManager.h"
#include "MyParallelServer.h"
#include "MyClientHandler.h"

#define T pair<int, int>

MatrixOfPairs* IntPairMatrixCreator::createMatrix(vector<string> matrixToBe) {
    vector<State<T>*> allStates;
    map<T, State<T>*> posAndStateMap;
    map<State<T>*, vector<State<T>*>> stateAndValidNeighborsMap;

    //count how many rows
    int rowsNum = 0;
    for (int i = 0; i < matrixToBe.size(); ++i) {
        if (matrixToBe[i] == LINE_SEPARATOR) {
            ++rowsNum;
        }
    }
    rowsNum -= 2; //substract the two additional lines of initials and goal states
    //count how many cols
    int colsNum = 0;
    int k = 0;
    while (matrixToBe[k] != LINE_SEPARATOR) {
        ++colsNum;
        ++k;
    }

    vector<string> matrixToBeCopy = matrixToBe;
    for (int i = 0; i < matrixToBeCopy.size(); ++i) {
        if (matrixToBeCopy[i] == LINE_SEPARATOR) {
            matrixToBeCopy.erase(matrixToBeCopy.begin() + i);
        }
    }

    int intMatrix[rowsNum][colsNum];
    for (int curRow = 0; curRow < rowsNum; ++curRow) {
        for (int curCol = 0; curCol < colsNum; ++curCol) {
            //offset = (IthRow * colsNum) + IthCol
            intMatrix[curRow][curCol] = stoi(matrixToBeCopy[((curRow * colsNum) + curCol)]);
        }
    }

    cout <<endl;
    for (int curRow = 0; curRow < rowsNum; ++curRow) {
        for (int curCol = 0; curCol < colsNum; ++curCol) {
            //offset = (IthRow * colsNum) + IthCol
            cout<< intMatrix[curRow][curCol] <<" ";
        }
        cout <<endl;
    }

    for (int curRow = 0; curRow < rowsNum; ++curRow) {
        for (int curCol = 0; curCol < colsNum; ++curCol) {
            T curPos = T(curRow, curCol);
            State<T>* singleState = new State<T>(curPos);
            singleState->setCost(intMatrix[curRow][curCol]);
            allStates.push_back(singleState);
            posAndStateMap[curPos] = singleState;
        }
    }

    //set neighbors
    for (int curRow = 0; curRow < rowsNum; ++curRow) {
        for (int curCol = 0; curCol < colsNum; ++curCol) {
            T curPos = T(curRow, curCol);
            State<T>* curState = posAndStateMap.at(curPos);
            T leftPos = T(curRow, curCol-1);
            T rightPos = T(curRow, curCol+1);
            T upPos = T(curRow-1, curCol);
            T downPos = T(curRow+1, curCol);
            vector<T> positions = {rightPos, downPos, leftPos, upPos};
            vector<State<T>*> possibleNeighbors;
            for (int i = 0; i < positions.size(); ++i) {
                if (posAndStateMap.count(positions[i]) && (posAndStateMap.at(positions[i])->getCost() != -1)) {
                    possibleNeighbors.push_back(posAndStateMap.at(positions[i]));
                }
            }
            stateAndValidNeighborsMap[curState] = possibleNeighbors;
        }
    }

    //set the initial and goal positions
    int numOfMatrixLineSeparators = rowsNum;
    int afterMatrixPos = rowsNum*colsNum + numOfMatrixLineSeparators;
    int initialI = stoi(matrixToBe[afterMatrixPos]);
    int initialJ = stoi(matrixToBe[afterMatrixPos + 1]);
    int goalI = stoi(matrixToBe[afterMatrixPos + 3]); //skip the lineSeparator
    int goalJ = stoi(matrixToBe[afterMatrixPos + 4]);
    pair<int, int> initialPos = pair<int, int>(initialI, initialJ);
    pair<int, int> goalPos = pair<int, int>(goalI, goalJ);
    State<T>* initialState = posAndStateMap.at(initialPos);
    State<T>* goalState = posAndStateMap.at(goalPos);

    //finally construct the matrix
    MatrixOfPairs *resMatrix;
    resMatrix = new MatrixOfPairs(allStates, initialState, goalState, stateAndValidNeighborsMap);
    //    list<State<T>*> allStates;
    //    State<T>* initialState;
    //    State<T>* goalState;
    //    map<class State<T>*,class list<State<T>*>> stateAndValidNeighborsMap;


    return resMatrix;
}

//int main() {

//
//    vector<string> matrixToBe;
////    matrixToBe.push_back(" 0, 1, 6, 2, 8, 2, 9, 4, 8, 7, 5, 9, 8, 0, 1, 3, 6, @, \n");
////    matrixToBe.push_back(" 4, 1, 0, 9,10, 0, 7, 9, 0, 1, 2, 8, 9, 3,10, 6, 7, @,\n");
////    matrixToBe.push_back(" 1, 7, 8, 9, 1, 0, 1,10,10, 0,10, 1, 0,10, 3, 7, 5, @,");
////    matrixToBe.push_back(" 0, 7, 6, 9,10, 5,10, 6, 3, 8, 0, 7, 9, 7, 1, 7, 1, @,");
////    matrixToBe.push_back(" 9, 1, 3, 5, 6, 0,10, 4, 1, 7, 4, 6, 6, 2, 8,10, 5, @,");
////    matrixToBe.push_back(" 2, 2, 1, 1, 6, 0, 6, 4, 9, 5, 6,10, 7, 3, 3,10, 5, @,");
////    matrixToBe.push_back(" 3, 0, 3,10, 1, 8,10, 4, 9, 4, 9, 0, 3, 1, 0, 3, 8, @,");
////    matrixToBe.push_back(" 4, 1, 4, 8, 9, 1, 9, 3, 7, 8, 5, 0, 5, 1, 4, 4, 0, @,");
////    matrixToBe.push_back("-1, 3, 9, 5, 5,10, 2, 3, 2, 8,10, 3, 5, 8, 6, 3, 2, @,");
////    matrixToBe.push_back(" 1, 4, 8,10, 9, 6, 0, 4, 0, 0, 5, 2,10, 3, 6, 8, 4, @,");
////    matrixToBe.push_back(" 0, 6, 2, 7, 1, 6, 4, 3, 4, 7, 6, 2, 7, 0, 5,10, 1, @,");
////    matrixToBe.push_back(" 9, 3, 0, 8, 8, 6, 7, 8, 0, 0, 1, 6, 3, 6, 4, 6, 9, @,");
////    matrixToBe.push_back(" 9, 6, 3, 6, 7, 3, 9, 5,10, 6, 7, 1, 3, 6, 9,10, 2, @,");
////    matrixToBe.push_back(" 7, 4, 3, 5, 4, 3, 6, 6, 6, 7, 2, 8, 4, 1, 6, 8, 0, @,");
////    matrixToBe.push_back(" 1, 2, 1, 2, 5, 2, 7, 0, 9, 3, 3, 4,10, 2, 1, 7, 9, @,");
////    matrixToBe.push_back(" 6, 5, 0, 3, 4,10, 3, 3, 0, 0, 5, 8, 0, 1, 9, 0, 9, @,");
////    matrixToBe.push_back(" 3, 2, 2, 3, 0, 4, 9, 3, 5, 3, 6, 5, 8, 4, 7, 6, 7, @,");
////    matrixToBe.push_back(" 0, 0, @,");
////    matrixToBe.push_back(" 16, 16, @,");
//
//    matrixToBe.push_back("0, 1, 2, @,");
//    matrixToBe.push_back("3, 4, 5, @,");
//    matrixToBe.push_back("6, 7, 8, @,");
//    matrixToBe.push_back("0, 0, @,");
//    matrixToBe.push_back("2, 2, @,");
//
//    vector<string> matrixToBeForReal;
//    for (int i = 0; i< matrixToBe.size(); ++i) {
//        vector<string> lexedBuffer = MyTestClientHandler::littleLexer(matrixToBe[i], ',');
//        matrixToBeForReal.insert(matrixToBeForReal.end(), lexedBuffer.begin(), lexedBuffer.end());
//        lexedBuffer.clear();
//    }
//
//    vector<string> matrixToBeForReal2 = matrixToBeForReal;
//    vector<string> matrixToBeForReal3 = matrixToBeForReal;
//    IntPairMatrixCreator intPairMatrixCreator;
//    MatrixOfPairs *matrixOfPairs1 = intPairMatrixCreator.createMatrix(matrixToBeForReal);
//    BestFirstSearch<T, string> bestFirstSearch;
//    string resPath = bestFirstSearch.search(matrixOfPairs1);
////    cout<< "total cost: "; cout<<resPath[resPath.size()-1]->getTotalCost() <<endl;
//    cout<< "numOfNodes: "; cout<<bestFirstSearch.getNumberOfNodesEvaluated()<<endl;
//    cout<<resPath<<endl;
////    cout<<resPath.size()<<endl;
//    DFS<T, string> dfs;
//    string strDfs = dfs.search(matrixOfPairs1);
//    cout<<strDfs<<endl;
//    MatrixOfPairs *matrixOfPairs2 = intPairMatrixCreator.createMatrix(matrixToBeForReal2);
//    BFS<T, string> bfs;
//    string strBfs = bfs.search(matrixOfPairs2);
//    cout<<strBfs<<endl;
//    MatrixOfPairs *matrixOfPairs3 = intPairMatrixCreator.createMatrix(matrixToBeForReal3);
//    Astar<T, string> astar;
//    string resPath3 = astar.search(matrixOfPairs3);
////    cout<< "total cost: "; cout<<resPath3[resPath3.size()-1]->getTotalCost() <<endl;
//    cout<< "numOfNodes: "; cout<<astar.getNumberOfNodesEvaluated()<<endl;
////    cout<<resPath3.size()<<endl;
//    cout<<resPath3<<endl;

//    FileCasheManager* fileCasheManager = new FileCasheManager;
//    fileCasheManager->saveSolution("ba'aya", "pitaron");
//    fileCasheManager->saveSolution("od ba'aya", "od pitaron");
//    fileCasheManager->saveSolution("yyy kama ba'ayot", "al tidag amar hadag");
//    delete fileCasheManager;
//    FileCasheManager* fileCasheManager2 = new FileCasheManager;
//    cout<< fileCasheManager2->getSolution("ba'aya")<<endl;
//    cout<< fileCasheManager2->getSolution("od ba'aya")<<endl;
//    cout<< fileCasheManager2->getSolution("yyy kama ba'ayot")<<endl;

//    server_side::MyParallelServer myParallelServer;
//
//    Isearcher<pair<int, int>, string>* iSearcher = new Astar<pair<int, int>, string>;
//    SearchSolver<Searchable<pair<int, int>>*, string, pair<int, int>>* solver
//    = new SearchSolver<Searchable<pair<int, int>>* , string, pair<int, int>>(iSearcher);
//    CacheManager<string, string>* cacheManager = new FileCasheManager;
//    ClientHandler* clientHandler = new MyClientHandler(solver, cacheManager);
//    myParallelServer.openServer(5400, clientHandler);


//}