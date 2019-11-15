#include <iostream> // cout, cin
#include <sys/socket.h> // socket, bind, listen, accept
#include <netinet/in.h> // IPPROTO_TCP, sockaddr_in,
// htons/ntohs, INADDR_ANY
#include <unistd.h> // close
#include <arpa/inet.h> // inet_ntop/inet_atop
#include <cstring> // strlen
#include <semaphore.h> // sem_init
#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <regex>

#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
#define BUFFER_SIZE 1024
#ifndef INC_1_TCPSERVER_H
#define INC_1_TCPSERVER_H
#define MAXTHREADCOUNT 3

class TCPServer
{
private:
    int PORTNUM;
    bool active;
    int threadCount;
    HANDLE semaphore;
    std::map <std::string, std::vector<int> > sensors;
    void InitializeSocket();
    static void ClientCommunication(void*);
    void IncrCounter();
    void DecrCounter();
    void updateSensors();
    void initSensors();
    std::string getSensortypes();
    std::string getSensor(const std::string&);
    std::string getAllSensors();
public:
    explicit TCPServer(int);
};

typedef struct {
    int clientSocket;
    sockaddr* saddr;
    TCPServer* self;
} socketParam;


#endif //INC_1_TCPSERVER_H
#endif