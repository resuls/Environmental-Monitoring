#include "TCPServer.h"

int main(int _argc, char **_argv)
{
    const int PORTNUM = atoi(_argv[1]);
    TCPServer server(PORTNUM);
}