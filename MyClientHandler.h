//
// Created by oryakov on 1/16/19.
//

#ifndef MILESTONE2_MYCLIENTHANDLER_H
#define MILESTONE2_MYCLIENTHANDLER_H

#define LINE_SEPARATOR "@"

#include <vector>
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "FileCasheManager.h"
#include "Searchable.h"
#include "IntPairMatrixCreator.h"
#include "MatrixOfPairs.h"
#include "SearchSolver.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>
#include <thread>
#include <fstream>
#include <algorithm>

class MyClientHandler : public ClientHandler {
    Solver<Searchable<pair<int, int>>*, string> *solver;
    CacheManager<string, string> *cacheManager;
public:
    MyClientHandler(SearchSolver<Searchable<pair<int, int>>*, string, pair<int, int>> *solver,
                    CacheManager<string, string> *cacheManager)
            : solver(solver), cacheManager(cacheManager) {}

    virtual void handleClient(int socket) {
        char buffer[1024];
        ssize_t n;
        int newsockfd = socket;
        string problem;
        vector<string> matrixToBe;
        /* If connection is established then start communicating */
        while (true) {
            bzero(buffer, 1024);
            n = read(newsockfd, buffer, 1023);

            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            string strBuffer = buffer;
            if ((strBuffer == "end\n") || (strBuffer == "end")) {
                break;
            }
            printf("Here is the message: %s\n", buffer);

            strBuffer += ",";
            vector<string> lexedBuffer = littleLexer(strBuffer, ',');
            lexedBuffer.push_back(LINE_SEPARATOR);
            matrixToBe.insert(matrixToBe.end(), lexedBuffer.begin(),
                              lexedBuffer.end());
            lexedBuffer.clear();

        }
        //matrix creator

        int probLength = (int) matrixToBe.size();
        for (int i = 0; i < probLength; ++i) {
            problem += matrixToBe[i];
        }
        string solution;
        if (cacheManager->isThereSolution(problem)) {
            solution = cacheManager->getSolution(problem);
        } else {
            IntPairMatrixCreator* intPairMatrixCreator = new IntPairMatrixCreator;
            MatrixOfPairs *matrixOfPairs = intPairMatrixCreator->createMatrix(matrixToBe);
            solution = solver->solve(matrixOfPairs);
            cacheManager->saveSolution(problem, solution);
            delete matrixOfPairs;
            delete intPairMatrixCreator;
            matrixToBe.clear();
        }
        const char *messageCstyle = solution.c_str();
        bzero(buffer, 1024);
        strcpy(buffer, messageCstyle);

        /* Write a response to the client */
        n = write(newsockfd, buffer, strlen(buffer));

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

        problem.clear();
        solution.clear();
        printf("bye\n");
        return;
    }

    static vector<string> littleLexer(string line, char c) {
        vector<string> res;
        char delimiter = c;
        string token;
        size_t pos = 0;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + 1);
            // delete tokes white spaces
            token.erase(remove(token.begin(), token.end(), ' '), token.end());
            token.erase(remove(token.begin(), token.end(), '\n'), token.end());
            res.push_back(token);
        }
        return res;
    }
};


#endif //MILESTONE2_MYCLIENTHANDLER_H
