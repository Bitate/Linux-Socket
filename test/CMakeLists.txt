cmake_minimum_required(VERSION 3.8)

set(this socketTest)

project(${this})

set(Source 
    serverTest.cpp
    clientTest.cpp
)

add_executable(${this} 
    ${Source}
)

target_include_directories(${this} PUBLIC ../src)
target_link_libraries(${this}
    gtest_main
    Socket
)
