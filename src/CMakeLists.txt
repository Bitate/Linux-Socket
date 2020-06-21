set(this Socket)

project(${this})

# TODO: Why cannot find files by using variables
add_executable(${this} socket.cpp socket.hpp)