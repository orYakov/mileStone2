//
// Created by oryakov on 1/15/19.
//

#ifndef MILESTONE2_MYPARALLELSERVER_H
#define MILESTONE2_MYPARALLELSERVER_H



#include "Sockets.h"
#include "ClientHandler.h"
#include <stack>
#include <thread>
#include <queue>
#include "Server.h"
#include <deque>
#include <mutex>

#define MAX_LISTEN 5
using namespace posix_sockets;


struct Args {
    int newsockfd;
};

namespace server_side {
    class MyParallelServer : public Server {

        bool first_run = true;

    public:
        void openServer(int port, ClientHandler *clientHandler) override {
            TCP_server server(port); //open server
            server.listen(MAX_LISTEN);
            mutex mutex1;
            std::stack<std::thread> threads;
            while (true) {

                try {
                    TCP_client client = server.accept();
                    //lock_guard<mutex> lock(mutex1);
                    threads.push(std::thread ([](ClientHandler * handler, int sock){handler->handleClient(sock);}, clientHandler, client.get_socket()));

                }   catch(timeout_exception& e) {
                    server.close();
                    break;
                }   catch (std::exception& e)   {
                    perror(e.what());
                    exit(1);
                }

                if (first_run)  {
                    server.settimeout(10);
                    first_run = false;

                }
            }
            while (!threads.empty())    {
                threads.top().join();
                threads.pop();
            }
        }


        void stopServer() override {

        }

        bool isOpen() override {
            return false;
        }
    };

}


#endif //MILESTONE2_MYPARALLELSERVER_H
