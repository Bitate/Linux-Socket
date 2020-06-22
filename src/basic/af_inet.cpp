// Create a specific AF_INET socket address

#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/stat.h>

#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;

// print error if any
static void failed(string functionName)
{
    perror( functionName.c_str());
    exit(1);
}

int main()
{
    int sock_inet;
    struct sockaddr_in adr_inet;
    // length of socket AF_INET address 
    int len_inet;
    const unsigned char ip[] = { 127, 0, 0, 23};

    // create a IPv4 internet socket
    sock_inet = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_inet == -1) 
        failed("socket()");

    // create an AF_INET address
    memset(&adr_inet, 0, sizeof(adr_inet));     // this is optional, but prefered practice
    adr_inet.sin_family = AF_INET;
    adr_inet.sin_port = htons(9000);
    memcpy(&adr_inet.sin_addr.s_addr, ip, 4);
    len_inet = sizeof(adr_inet);    // AF_INET address struct has fixed length/size

    // bind AF_INET address to socket
    int bind_result = bind(sock_inet, (struct sockaddr*)&adr_inet, len_inet);
    if(bind_result == -1)
        failed("bind()");

    // print all of our bound sockets
    // TODO: fix command error
    system("netstat -pa --tcp 2>/dev/null");

    close(sock_inet);
}