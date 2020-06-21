cmake_minimum_required(VERSION 3.8)

set(this socketTest)

project(${this})

add_executable(${this} socketTest.cpp)
target_include_directories(${this} PUBLIC ../src)
target_link_libraries(${this}
    gtest_main
    Socket
)
