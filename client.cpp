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
using namespace std;

int main(int _argc, char **_argv)
{
    //  Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (client_socket < 0)
    {
        cout << "Error while creating a socket\n";
        exit(-1);
    }
    else
    {
        cout << "created socket\n";
    }

    // connect
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5559);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(server_address.sin_zero), '\0', 8);

    if (connect(client_socket, (sockaddr*) &server_address, sizeof(server_address)) < 0)
    {
        cout << "Error on connect\n";
        exit(-1);
    } else
    {
        cout << "Successfully connected\n";
    }

    // Send
    char* send_msg = "Hello World from Client!\0";
    int msgSize = strlen(send_msg); // check size!

    int sVal = send(client_socket, send_msg, msgSize + 1, 0);

    if (sVal < 0)
    {
        cout << "Error on sending\n";
    }
    else
    {
        cout << "Successfully sent\n";
    }

    // Receive
    char rcv_msg[BUFFER_SIZE];
    int rVal = recv(client_socket, rcv_msg, BUFFER_SIZE, 0);
    if (rVal < 0)
    {
        cout << "Error on receive!\n";
    }
    else if (rVal == 0)
    {
        cout << "Communication interrupted!\n";
    }
    else
    {
        cout << "Successfully received message of size " << rVal << "\n";
        cout << rcv_msg << endl;
    }
}

#endif