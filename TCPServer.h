#include <iostream> // cout, cin
#include <sys/socket.h> // socket, bind, listen, accept
#include <netinet/in.h> // IPPROTO_TCP, sockaddr_in,
// htons/ntohs, INADDR_ANY
#include <unistd.h> // close
#include <arpa/inet.h> // inet_ntop/inet_atop
#include <cstring> // strlen
#include <semaphore.h> // sem_init

#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
#define BUFFER_SIZE 1024
#ifndef INC_1_TCPSERVER_H
#define INC_1_TCPSERVER_H

class TCPServer
{
private:
    int PORTNUM;
    bool mActive;
    void InitializeSocket();
    void ClientCommunication(int client_comm);

public:
    explicit TCPServer(int _portnum);
};

#endif //INC_1_TCPSERVER_H
#endif