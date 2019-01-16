//
// Created by oryakov on 1/6/19.
//
#define LINE_SEPARATOR "@"

#include "MyTestClientHandler.h"
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

void MyTestClientHandler::handleClient(int socket) {
    char buffer[256];
    ssize_t n;
    int newsockfd = socket;
    string problem;
    vector<string> matrixToBe;
    /* If connection is established then start communicating */
    while (true) {
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);

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

        //string problem = strBuffer;

    }
    //matrix creator

    string solution;
    if (cacheManager->isThereSolution(problem)) {
        solution = cacheManager->getSolution(problem);
    } else {
        solution = solver->solve(problem);
        cacheManager->saveSolution(problem, solution);
    }
    const char *messageCstyle = solution.c_str();
    bzero(buffer, 256);
    strcpy(buffer, messageCstyle);

    /* Write a response to the client */
    n = write(newsockfd, buffer, strlen(buffer));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

    printf("bye\n");
}

vector<string> MyTestClientHandler::littleLexer(string line, char c) {
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
