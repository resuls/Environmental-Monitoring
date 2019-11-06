#include "TCPServer.h"
#include "UDPServer.h"

int getMenu();

int main(int _argc, char **_argv)
{
    const int PORTNUM = atoi(_argv[1]);

    int choice = getMenu();

    if (choice == 1)
    {
        TCPServer server(PORTNUM);
    } else if (choice == 2)
    {
        UDPServer udpServer(PORTNUM);
    }
    else if (choice == 4)
        return 0;
}

int getMenu()
{
    int choice;

    printf("C++ Server Menu:\n");
    printf("----------------\n");
    printf("1. Start TCP v4 Server\n"
           "2. Start TCP v6 Server\n"
           "3. Start UDP Echo Server\n"
           "4. EXIT\n");
    printf("--------------------\n");

    scanf("%d", &choice);

    return choice;
}