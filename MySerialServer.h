//
// Created by oryakov on 1/3/19.
//

#ifndef MILESTONE2_MYSERIALSERVER_H
#define MILESTONE2_MYSERIALSERVER_H

#include "Server.h"

using namespace server_side;
class MySerialServer : public Server {

public:
    virtual void open(int port, ClientHandler* c);

    void static createServer(int port, ClientHandler* c, int clientsNum);

    virtual void stop();
};


#endif //MILESTONE2_MYSERIALSERVER_H
