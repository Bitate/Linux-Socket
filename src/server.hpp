#pragma once
#include <sys/socket.h>
#include <string>

class Server
{
    public:
    Server();
    ~Server();
    Server( const Server& ) = default;
    Server( Server&& ) = default;
    Server& operator=( const Server& ) = default;
    Server& operator=( Server&& ) = default;

    public:
    bool listenAt( std::string host_name, int port);

};