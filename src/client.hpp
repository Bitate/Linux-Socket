#pragma once
#include <sys/socket.h>
#include <string>

class Client
{
    public:
    Client();
    ~Client();
    Client( const Client& ) = default;
    Client( Client&& ) = default;
    Client& operator=( const Client& ) = default;
    Client& operator=( Client&& ) = default;

    public:
    

};