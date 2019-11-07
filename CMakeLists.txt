# cmake_minimum_required(VERSION <specify CMake version here>)
project(1)

set(CMAKE_CXX_STANDARD 17)

add_executable(main servermain.cpp TCPServer.cpp TCPServer.h UDPServer.cpp UDPServer.h TCPServerV6.cpp TCPServerV6.h)
add_executable(tcp tcpclient.cpp)
add_executable(udp udpclient.cpp)
add_executable(tcpv6 tcpv6client.cpp)