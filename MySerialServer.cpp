//
// Created by oryakov on 1/3/19.
//

#include "MySerialServer.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>
#include <thread>
#include <fstream>

void MySerialServer::open(int port, ClientHandler* c) {
    int clientNum = 5;
    thread serverThread(createServer, port, c, clientNum);
    serverThread.detach();
    }

void MySerialServer::createServer(int port, ClientHandler *c, int clientsNum) {
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        throw "cannot open socket";
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        throw "cannot bind socket";
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */
    listen(sockfd, clientsNum);
    clilen = sizeof(cli_addr);

    for (int i = 0; i< clientsNum; ++i) {
        /* Accept actual connection from the client */
        cout<<"server Try to connect"<<endl;
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
                           (socklen_t *) &clilen);
        cout<<"server connection successful"<< endl;
        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        cout<< "treating client no. " << i <<endl;
        c->handleClient(newsockfd);
        cout<< "client no. " << i <<" done" <<endl;
    }

}

void MySerialServer::stop() {

}

