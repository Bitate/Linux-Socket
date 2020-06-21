cmake_minimum_required(VERSION 3.8)

set(this Linux-Socket)

project(${this})

enable_testing()
add_subdirectory(googletest)
add_subdirectory(src)
add_subdirectory(test)

