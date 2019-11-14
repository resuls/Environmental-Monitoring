# cmake_minimum_required(VERSION <specify CMake version here>)
project(1)

set(CMAKE_CXX_STANDARD 17)

add_executable(main_menu ServerAndClientTemplates/servermain.cpp ServerAndClientTemplates/TCPServer.cpp ServerAndClientTemplates/TCPServer.h ServerAndClientTemplates/UDPServer.cpp ServerAndClientTemplates/UDPServer.h ServerAndClientTemplates/TCPServerV6.cpp ServerAndClientTemplates/TCPServerV6.h)
add_executable(tcp_template ServerAndClientTemplates/tcpclient.cpp)
add_executable(udp_template ServerAndClientTemplates/udpclient.cpp)
add_executable(tcpv6_template ServerAndClientTemplates/tcpv6client.cpp)
add_executable(tcpserver servermain.cpp TCPServer.cpp TCPServer.h)
add_executable(tcpclient tcpclient.cpp)