//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//
//#include <netdb.h>
//#include <unistd.h>
//#include <netinet/in.h>
//
//#include <string.h>
//
//#include <sys/socket.h>
//#include <thread>
//#include "MySerialServer.h"
//#include "MyTestClientHandler.h"
//
//using namespace std;
//
//void createServer(int port, int waitTime, int* retSockfd, bool* shouldStop) {
//    int sockfd, newsockfd, portno, clilen;
//    char buffer[256];
//    struct sockaddr_in serv_addr, cli_addr;
//    int n;
//
//
//    /* First call to socket() function */
//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//
//    if (sockfd < 0) {
//        perror("ERROR opening socket");
//        throw "cannot open socket";
//    }
//
//    /* Initialize socket structure */
//    bzero((char *) &serv_addr, sizeof(serv_addr));
//    portno = port;
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_addr.s_addr = INADDR_ANY;
//    serv_addr.sin_port = htons(portno);
//
//    /* Now bind the host address using bind() call.*/
//    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
//        perror("ERROR on binding");
//        throw "cannot bind socket";
//    }
//
//    /* Now start listening for the clients, here process will
//       * go in sleep mode and will wait for the incoming connection
//    */
//
//    listen(sockfd, 5);
//    clilen = sizeof(cli_addr);
//
//    /* Accept actual connection from the client */
//    cout<<"server Try to connect"<<endl;
//    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
//                       (socklen_t *) &clilen);
//    cout<<"server connection succesful"<< endl;
//    if (newsockfd < 0) {
//        perror("ERROR on accept");
//        throw "error in accepting socket";
//    }
//    *retSockfd = sockfd;
//
//    cout<< "server sockfd " <<sockfd<<endl;
//    cout<< "server new_sockfd " <<newsockfd<<endl;
//    /* If connection is established then start communicating */
//    bool stop = *shouldStop;
//    while (true) {
//        bzero(buffer, 256);
//        n = read(newsockfd, buffer, 255);
//        //fflush(stdin);
//
//        if (n < 0) {
//            perror("ERROR reading from socket");
//            throw "cannot read socket";
//        }
//        string strBuffer = buffer;
//        if (strBuffer == "end\n") {
//            //printf("bye\n");
//            break;
//        }
//        printf("Here is the message: %s\n", buffer);
////        stop = *shouldStop;
////        if (stop) {
////            printf("bye\n");
////            break;
////        }
//        //usleep(500*1000);
//    }
//    //close(sockfd);
//    printf("bye\n");
//}
//
//void connectToServer(string ip, int port, int* retSockfd) {
//    //mutex mutex1;
//    int sockfd, portno, n;
//    struct sockaddr_in serv_addr;
//    struct hostent *server;
//
//    portno = port;
//
//    /* Create a socket point */
//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//
//    if (sockfd < 0) {
//        perror("ERROR opening socket");
//        exit(1);
//    }
//
//    const char *ipCstyle = ip.c_str();
//    server = gethostbyname(ipCstyle);
//
//    if (server == nullptr) {
//        perror("ERROR, no such host");
//        exit(1);
//    }
//
//    bzero((char *) &serv_addr, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//    bcopy(server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
//          server->h_length);
//    serv_addr.sin_port = htons(portno);
//
//    /* Now connect to the server */
//    cout << "client trying to connect" << endl;
////    char c;
////    scanf("c", &c);
//    //mutex1.unlock();
//    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <
//        0) {
//        perror("ERROR connecting");
//        throw "ERROR connecting";
//    }
//    cout << "client connect successful" << endl;
//    *retSockfd = sockfd;
//    cout<< "client sockfd " <<sockfd<<endl;
//}
//
//void sendData(string path, double value, int sockfd) {
//    if (sockfd == -1) {
//        return;
//    }
//    /* Now ask for a message from the user, this message
//       * will be read by server
//    */
//    ssize_t n;
//    char buffer[256];
//    string message;
//    string strValue = to_string(value);
//    message = "set " + path + " " + strValue + " \r\n";
//    if (path == "end") {
//        message = "end";
//        message += "\n";
//    }
//    const char *messageCstyle = message.c_str();
//    bzero(buffer, 256);
//    strcpy(buffer, messageCstyle);
//
//    /* Send message to the server */
//    n = write(sockfd, buffer, strlen(buffer));
//    //fflush(stdout);
//    if (n < 0) {
//        perror("ERROR writing to socket");
//        exit(1);
//    }
//    usleep(250*1000);
//
//    if (message != "end\n") {
//        /* Now read server response */
//        bzero(buffer,256);
//        n = read(sockfd, buffer, 255);
//
//        if (n < 0) {
//            perror("ERROR reading from socket");
//            exit(1);
//        }
//
//        printf("%s\n",buffer);
//    }
//
//}
//
//
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    bool shouldStop = false;
//    int clientSockfd1;
//    int serverSockfd;
//    MySerialServer mySerialServer;
//    ClientHandler* clientHandler = new MyTestClientHandler;
//    mySerialServer.open(5400, clientHandler);
////    thread serverThread(createServer, 5400, 10, &serverSockfd, &shouldStop);
////    serverThread.detach();
//    char c;
//    scanf("c ", &c);
//    connectToServer("192.168.85.137", 5400, &clientSockfd1);
//    sendData("/path/bla/bla/bla", 30.0, clientSockfd1);
//    //usleep(500*1000);
//    sendData("/path/bla/bla/bla", 40.0, clientSockfd1);
//    //usleep(500*1000);
//    sendData("/path/bla/bla/bla", 50.0, clientSockfd1);
//    //serverThread.detach();
//    //serverThread.join();
//    sendData("/path/bla/bla/bla", 60.0, clientSockfd1);
//    sendData("/path/bla/bla/bla", 70.0, clientSockfd1);
//    //usleep(250*1000);
//    //shouldStop = true;
////    sendData("end", 70.0, clientSockfd1);
//    //usleep(1000*1000);
//    sendData("end", 70.0, clientSockfd1);
//    close(clientSockfd1);
//    usleep(250*1000);
//    //close(serverSockfd);
////    printf("enter c\n");
////    char s;
////    scanf(" s", &s);
////    if (s == 'y') {
////        shouldStop = true;
////    }
//    int clientSockfd2;
//    //thread serverThread(createServer, 5400, 10, &serverSockfd, &shouldStop);
//    //serverThread.detach();
//    char a;
//    scanf("c ", &a);
//    connectToServer("192.168.85.137", 5400, &clientSockfd2);
//    sendData("/path/bla/bla/bla", 80.0, clientSockfd2);
//    //usleep(500*1000);
//    sendData("/path/bla/bla/bla", 90.0, clientSockfd2);
//    //usleep(500*1000);
//    sendData("/path/bla/bla/bla", 100.0, clientSockfd2);
//    //serverThread.detach();
//    //serverThread.join();
//    sendData("/path/bla/bla/bla", 110.0, clientSockfd2);
//    sendData("/path/bla/bla/bla", 120.0, clientSockfd2);
//    //usleep(250*1000);
//    //shouldStop = true;
//    sendData("end", 70.0, clientSockfd2);
//    //usleep(1000*1000);
//    close(clientSockfd2);
//    usleep(250*1000);
//
//    return 0;
//}

#include "MyParallelServer.h"
#include "Isearcher.h"
#include "Astar.h"
#include "CacheManager.h"
#include "MyClientHandler.h"

int main(int argc, char* argv[]) {

    int port = stoi(argv[1]);
    server_side::MyParallelServer myParallelServer;

    Isearcher<pair<int, int>, string>* iSearcher = new Astar<pair<int, int>, string>;
    SearchSolver<Searchable<pair<int, int>>*, string, pair<int, int>>* solver
                                                                        = new SearchSolver<Searchable<pair<int, int>>* , string, pair<int, int>>(iSearcher);
    CacheManager<string, string>* cacheManager = new FileCasheManager;
    ClientHandler* clientHandler = new MyClientHandler(solver, cacheManager);
    myParallelServer.openServer(port, clientHandler);





    return 0;
}