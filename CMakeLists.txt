# cmake_minimum_required(VERSION <specify CMake version here>)
project(1)

set(CMAKE_CXX_STANDARD 17)

add_executable(client client.cpp)
add_executable(tcp servermain.cpp TCPServer.cpp TCPServer.h)
add_executable(udp  UDPServer.cpp UDPServer.h)