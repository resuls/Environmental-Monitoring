#include "TCPServer.h"

TCPServer::TCPServer(int _portnum)
{
    PORTNUM = _portnum;
    mActive = true;
    InitializeSocket();
}

void TCPServer::InitializeSocket()
{
    sockaddr_in server_address{};
    int server_socket{};

    //  Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (server_socket < 0)
    {
        std::cout << "Error while creating a socket\n";
        return;
    }
//    else
//    {
//        std::cout << "created socket\n";
//    }

    // Bind
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORTNUM);
    memset(&(server_address.sin_zero), '\0', 8);

    if (bind(server_socket, (sockaddr *) &server_address, sizeof(server_address)) < 0)
    {
        std::cout << "ERROR on binding\n";
        return;
    }
//    else
//    {
//        std::cout << "bound to port\n";
//    }

    // Listen
    if (listen(server_socket, 5) < 0)
    {
        std::cout << "Error on listening!\n";
        return;
    }
    else
    {
        std::cout << "Listening...\n";
    }

    // Accept
    int client_comm;
    do
    {
        client_comm = accept(server_socket, nullptr, nullptr);
        std::cout << "Client connected..." << std::endl;
        ClientCommunication(client_comm);
    } while (mActive);
}

void TCPServer::ClientCommunication(int client_comm)
{
    while (true)
    {
        char rcv_msg[BUFFER_SIZE];
        int rVal = recv(client_comm, rcv_msg, BUFFER_SIZE, 0);
        if (rVal < 0)
        {
            std::cout << "Error on receive!\n";
            break;
        } else if (rVal == 0)
        {
            std::cout << "Communication interrupted!\n";
            break;
        } else
        {
            std::cout << "Message: " << rcv_msg << "\n";
        }

        if (rVal > 0)
        {
            char *msg = "ACK\0";
            int msgSize = strlen(msg);
            int sVal = send(client_comm, msg, msgSize + 1, 0);

            if (sVal < 0)
            {
                std::cout << "Error on sending\n";
                break;
            }
//            else
//            {
//                std::cout << "Successfully sent\n";
//            }
        }
    }

    if (close(client_comm) < 0)
    {
        std::cout << "Couldn't client communication!\n";
    } else
    {
        std::cout << "Closed client communication!\n";
    }
}
