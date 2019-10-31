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
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (server_socket < 0)
    {
        cout << "Error while creating a socket\n";
        exit(-1);
    }
    else
    {
        cout << "created socket\n";
    }

    // Bind
    sockaddr_in server_address{};
    const int PORTNUM = 5559;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORTNUM);
    memset(&(server_address.sin_zero), '\0', 8);

    if (bind(server_socket, (sockaddr*) &server_address, sizeof(server_address)) < 0)
    {
        cout << "ERROR on binding\n";
        exit(-1);
    }
    else
    {
        cout << "bound to port\n";
    }

    // Listen
    if (listen(server_socket, 5) < 0)
    {
        cout << "Error on listening!\n";
        exit(-1);
    } else
    {
        cout << "Listening...\n";
    }

    // Accept
    int client_address = accept(server_socket, nullptr, nullptr);

    // Receive
    char rcv_msg[BUFFER_SIZE];
    int rVal = recv(client_address, rcv_msg, BUFFER_SIZE, 0);
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

    // Send
    char* send_msg = "Hello World from Server!\0";
    int msgSize = strlen(send_msg); // check size!
    int sVal = send(client_address, send_msg, msgSize + 1, 0);

    if (sVal < 0)
    {
        cout << "Error on sending\n";
    }
    else
    {
        cout << "Successfully sent\n";
    }
}

#endif