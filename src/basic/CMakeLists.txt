cmake_minimum_required(VERSION 3.8)

set(this Basic)

project(${this})

add_executable(createSocket createSocket.cpp)
add_executable(socketPair socketPair.cpp)