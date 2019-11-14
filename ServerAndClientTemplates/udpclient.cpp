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
    const int PORTNUM = atoi(_argv[1]);
    const char* SERVERIP = _argv[2];

    //  Create socket
    int client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (client_socket < 0)
    {
        cout << "Error while creating a socket\n";
        exit(-1);
    }
    else
    {
        cout << "created socket\n";
    }

    while (true)
    {
        // Read message
        char send_msg[100];
        cout << "Enter message: ";
        cin.getline(send_msg, 100);

        if (strcmp(send_msg, "EXIT") == 0)
        {
            break;
        }

        sockaddr_in server_address{};
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(PORTNUM);
        server_address.sin_addr.s_addr = inet_addr(SERVERIP);
        memset(&(server_address.sin_zero), '\0', 8);
        int toSize = sizeof(server_address);

        // Send message
        int msgSize = strlen(send_msg); // check size!
        int sVal = sendto(client_socket, send_msg, msgSize + 1, 0, (sockaddr*)&server_address, toSize);
        if (sVal < 0)
        {
            cout << "Error on sending\n";
            break;
        }
        else
        {
            cout << "Successfully sent\n";
        }

        // Receive
        char rcv_msg[BUFFER_SIZE];
        int rVal = recvfrom(client_socket, rcv_msg, BUFFER_SIZE, 0, (sockaddr*)&server_address, &toSize);
        if (rVal < 0)
        {
            cout << "Error on receive!\n";
            break;
        }
        else if (rVal == 0)
        {
            cout << "Communication interrupted!\n";
            break;
        }
        else
        {
            cout << "Successfully received message of size " << rVal << "\n";
            cout << rcv_msg << endl;
        }
    }

    if (close(client_socket) < 0)
    {
        cout << "Couldn't close socket!\n";
    }
    else
    {
        cout << "Closed socket!\n";
    }
}

#endif