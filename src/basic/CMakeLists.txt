cmake_minimum_required(VERSION 3.8)

set(this Basic)

project(${this})

add_executable(socketPair socketPair.cpp)
add_executable(clientServer clientServer.cpp)
add_executable(af_unix af_unix.cpp)
add_executable(af_unix2 af_unix2.cpp)