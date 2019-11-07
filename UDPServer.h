#include <iostream> // cout, cin
#include <sys/socket.h> // socket, bind, listen, accept
#include <netinet/in.h> // IPPROTO_TCP, sockaddr_in,
// htons/ntohs, INADDR_ANY
#include <unistd.h> // close
#include <arpa/inet.h> // inet_ntop/inet_atop
#include <cstring> // strlen
#include <semaphore.h> // sem_init

#define BUFFER_SIZE 1024
#ifndef INC_1_UDPSERVER_H
#define INC_1_UDPSERVER_H

class UDPServer
{
private:
    int PORTNUM;
    bool mActive;
    void InitializeSocket();
    void ClientCommunication(int _udpSocket);

public:
    explicit UDPServer(int _portnum);
};

#endif //INC_1_UDPSERVER_H