#include <random>
#include "TCPServer.h"

TCPServer::TCPServer(int _portnum)
{
    PORTNUM = _portnum;
    active = true;
    threadCount = 0;
    initSensors();
    updateSensors();
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
        std::string message = "";

        char rcv_msg[BUFFER_SIZE] = "\0";
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
            message = rcv_msg;
        }

        std::string reply = "";
        std::regex types ("getSensortypes\\(\\)");
        std::regex all ("getAllSensors\\(\\)");
        std::regex sensor ("getSensor\\(.+\\)");
        if (rVal > 0)
        {
            if (std::regex_search(message, types))
            {
                reply = self->getSensortypes();
            }
            else if (std::regex_search(message, all))
            {
                reply = self->getAllSensors();
            }
            else if (std::regex_search(message, sensor))
            {
                int start = message.find('(') + 1;
                int end = message.find(')');
                std::string argument = message.substr(start, end - start);
                reply = self->getSensor(argument);
            }
            else
            {
                reply = "No method found!";
            }

            reply += "\n";
            int sVal = send(clientSocket, reply.c_str(), reply.size(), 0);
            if (sVal < 0)
            {
                std::cout << "Error on sending\n";
                break;
            }
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

void TCPServer::initSensors()
{
    sensors["air"] = {};
    sensors["noise"] = {};
    sensors["light"] = {};
}

void TCPServer::updateSensors()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> counts(1, 10);
    for (auto& s : sensors)
    {
        int count = counts(mt);
        std::uniform_int_distribution<int> values(1, 1000);
        for (int i = 0; i < count; i++)
        {
            int val = counts(mt);
            s.second.push_back(val);
        }
    }
}

std::string TCPServer::getSensortypes()
{
    std::string res;
    for (const auto& s : sensors)
    {
        res += s.first + ";";
    }
    res.pop_back();
    return res;
}

std::string TCPServer::getSensor(const std::string& sensor)
{
    std::string res;
    auto iter = sensors.find(sensor);
    if (iter != sensors.end())
    {
        std::time_t time = std::time(nullptr);
        res += std::to_string(time) + "|";

        for (auto i : iter->second)
        {
            res += std::to_string(i) + ";";
        }

        res.pop_back();
    }

    if (res.empty())
        return "";
    return res;
}

std::string TCPServer::getAllSensors()
{
    std::time_t time = std::time(nullptr);
    std::string res = std::to_string(time) + "|";

    for (const auto& s : sensors)
    {
        res += s.first + ";";
        for (auto i : s.second)
        {
            res += std::to_string(i) + ";";
        }
        res.pop_back();
        res += "|";
    }
    res.pop_back();

    return res;
}
