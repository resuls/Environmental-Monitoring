#include "TCPServer.h"

TCPServer::TCPServer(int _portnum)
{
    PORTNUM = _portnum;
    active = true;
    threadCount = 0;
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
    } else
    {
        std::cout << "Listening...\n";
    }

    // Create a semaphore with initial and max counts of MAX_SEM_COUNT
    semaphore = CreateSemaphoreA(
            nullptr,           // default security attributes
            threadCount,               // initial count
            MAXTHREADCOUNT,                       // maximum count
            nullptr);                     // unnamed semaphore

    if (semaphore == nullptr)
    {
        std::cout << "CreateSemaphore error\n";
        return;
    }

    // Accept
    typedef void * (*THREADFUNCPTR)(void *);
    do
    {
        sockaddr_in client_address{};
        int size = sizeof(client_address);
        int clientSocket = ::accept(server_socket, (sockaddr*)&client_address, (socklen_t*) &size);

        pthread_t t;
        auto* parameter = new socketParam();
        parameter->clientSocket = clientSocket;
        parameter->saddr = (sockaddr*)&client_address;
        parameter->self = this;

        int res = pthread_create(&t, nullptr, (THREADFUNCPTR) &TCPServer::ClientCommunication, parameter);
    } while (active);

    ReleaseSemaphore(semaphore, 1, nullptr);
}

void TCPServer::ClientCommunication(void* _parameter)
{
    auto* p = (socketParam*)_parameter;
    int clientSocket = p->clientSocket;
    TCPServer* self = p->self;
    bool shouldConnect = true;

    if (self->threadCount < MAXTHREADCOUNT)
    {
        std::cout << "Client connected..." << std::endl;
        self->IncrCounter();
    }
    else
    {
        shouldConnect = false;
        std::cout << "Max thread limit reached!" << std::endl;
    }

    while (shouldConnect)
    {
        char rcv_msg[BUFFER_SIZE];
        int rVal = recv(clientSocket, rcv_msg, BUFFER_SIZE, 0);
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
            int sVal = send(clientSocket, msg, msgSize + 1, 0);

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

    if (close(clientSocket) < 0)
    {
        std::cout << "Couldn't close client communication!\n";
    } else
    {
        std::cout << "Closed client communication!\n";
    }
    self->DecrCounter();
}

void TCPServer::IncrCounter()
{
    if (threadCount < MAXTHREADCOUNT)
        threadCount++;

    std::cout << "Connected clients: " << threadCount << std::endl;
}

void TCPServer::DecrCounter()
{
    if (threadCount > 0)
        threadCount--;
}