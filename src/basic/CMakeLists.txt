cmake_minimum_required(VERSION 3.16)

set(this Basic)

project(${this})

add_executable(socketPair socketPair.cpp)
add_executable(clientServer clientServer.cpp)
add_executable(af_unix af_unix.cpp)
add_executable(af_unix2 af_unix2.cpp)
add_executable(af_inet af_inet.cpp)
add_executable(epoll epoll.c)
