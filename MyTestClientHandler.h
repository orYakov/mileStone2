//
// Created by oryakov on 1/6/19.
//

#ifndef MILESTONE2_MYTESTCLIENTHANDLER_H
#define MILESTONE2_MYTESTCLIENTHANDLER_H

#include <vector>
#include "ClientHandler.h"
//#include "Solver.h"
//#include "CacheManager.h"
#include "StringReverser.h"
#include "FileCasheManager.h"
class MyTestClientHandler : public ClientHandler{
Solver<string, string>* solver = new StringReverser;
CacheManager<string, string>* cacheManager = new FileCasheManager;

public:
    virtual void handleClient(int socket);
    static vector<string> littleLexer(string line, char c);
};


#endif //MILESTONE2_MYTESTCLIENTHANDLER_H
