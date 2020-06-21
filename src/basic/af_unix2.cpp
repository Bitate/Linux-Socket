// create an abstract named AF_LOCAL/AF_UNIX socket.

#include <sys/unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <string>
#include <iostream>


using namespace std;

// print error if any
static void failed( string functionName)
{
    perror(functionName.c_str());
}


int main()
{
    int status;
    int socket_handler;
    struct sockaddr_un af_unix;
    int len_unix;
    const char path_unix[] = "Z*MY_SOCKET*";

    // create socket
    socket_handler = socket(AF_UNIX, SOCK_STREAM, 0);
    if(socket_handler == -1)
    {
        failed("socket()");
    }

    // generate an AF_UNIX address
    memset(&af_unix, 0, sizeof(af_unix));

    af_unix.sun_family = AF_UNIX;
    strncpy(af_unix.sun_path, path_unix, (sizeof(af_unix) -1) );

    len_unix = SUN_LEN(&af_unix);

    // bind the address to socket
    status = bind(socket_handler, (struct sockaddr*)& af_unix, len_unix);
    if (status == -1 )
    {
        failed("bind()");
    }

    // display all of our bound sockets
    system("netstat -pa --unix 2>/dev/null |" 
        "sed -n '/^Active UNIX/,/^Proto/p;"
        "/af_unix/p'");

    // close and unlink our socket path
    close(socket_handler);
}