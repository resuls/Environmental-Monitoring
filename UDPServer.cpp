#include "UDPServer.h"

UDPServer::UDPServer(int _portnum)
{
    PORTNUM = _portnum;
    mActive = true;
    InitializeSocket();
}

void UDPServer::InitializeSocket()
{
    sockaddr_in server_address{};
    int udpSocket{};

    //  Create socket
    udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (udpSocket < 0)
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

    if (bind(udpSocket, (sockaddr *) &server_address, sizeof(server_address)) < 0)
    {
        std::cout << "ERROR on binding\n";
        return;
    }
//    else
//    {
//        std::cout << "bound to port\n";
//    }

    do
    {
        std::cout << "Client connected..." << std::endl;
        ClientCommunication(udpSocket);
    } while (mActive);
}

void UDPServer::ClientCommunication(int udpSocket)
{
    while (true)
    {
        char rcv_msg[BUFFER_SIZE];
        sockaddr_in from{};
        int fromSize = sizeof(from);

        int rVal = recvfrom(udpSocket, rcv_msg, BUFFER_SIZE, 0, (sockaddr*)&from , &fromSize);
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
            char msg[BUFFER_SIZE];
            msg[0] = '\0';
            char *echo = "ECHO: ";
            strcat(msg, echo);
            strcat(msg, rcv_msg);

            int msgSize = strlen(msg);
            int sVal = sendto(udpSocket, msg, msgSize + 1, 0, (sockaddr*)&from, fromSize);

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

    if (close(udpSocket) < 0)
    {
        std::cout << "Couldn't client communication!\n";
    } else
    {
        std::cout << "Closed client communication!\n";
    }
}
