// AF_UNIX Socket Demo

#include <unistd.h>
#include <string>
#include <sys/un.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;

int main()
{
    // socket file descriptor
    int socketfd;
    // socket operation status
    int status;
    // socket name structure
    struct sockaddr_un af_unix;
    // socket address length
    int len_unix;
    // path of local file system
    const char path_unix[] = "/tmp/my_sock";

    // create a AF_UNIX (aka AF_LOCAL) socket
    socketfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(socketfd == -1)
    {
        perror("socket()");
        exit(1);
    }

    // the AF_UNIX address results in a file
    // system object being created, it must be 
    // removed when it's no longer needed
    unlink(path_unix);

    // form a AF_UNIX address
    memset(&af_unix, 0, sizeof(af_unix));

    af_unix.sun_family = AF_UNIX;
    strncpy(af_unix.sun_path, path_unix, (sizeof(af_unix.sun_path) - 1));

    len_unix = SUN_LEN(&af_unix);

    // bind address to the socket.
    status = bind(socketfd, (struct sockaddr*)&af_unix, len_unix);
    if(status == -1)
    {
        perror("bind()");
        exit(1);
    }

    // display all of our bound sockets
    system("netstat -pa --unix 2>/dev/null| " "sed -n '/^Active UNIX/,/^Proto/p;" "/af_unix/p'");

    // close and unlink our socket path
    close(socketfd);
    unlink(path_unix);

}