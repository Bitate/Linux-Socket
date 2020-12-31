cmake_minimum_required(VERSION 3.16)

project("linux_programming")

enable_testing()
add_subdirectory(googletest)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(tlpi)

