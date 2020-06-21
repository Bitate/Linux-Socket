#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    // socket pair
    int s[2];

    // create a pair of local sockets
    int status = socketpair(AF_LOCAL, SOCK_STREAM, 0, s);
    if(status == -1)
    {
        cout << "Fail to create socket pair" << endl;
    }

    // print the socket file descriptors returned
    cout << "s[0] is " << s[0] << endl;
    cout << "s[1] is " << s[1] << endl;

    string message = "Hello, I'm s[0]";
    char buffer[80];
    // write a message to socket s[1]
    status = write(s[1], message.c_str(), message.size());
    if(status < 0)
    {
        cout << "Fail to write to socket" << endl;
    }
    else
    {
        cout << "Send: " << message << endl;
    }

    // read a message from socket s[0]
    status = read(s[0], buffer, sizeof(buffer));
    if(status < 0)
    {
        cout << "Fail to read from socket" << endl;
    }
    else
    {
        cout << "Receive: " << buffer << endl;
    }

    // reply to s[1]
    message = "Go away";
    status = write(s[0], message.c_str(), message.size());
    if(status < 0)
    {
        cout << "Fail to reply" << endl;
    }
    else
    {
        cout << "Reply: " << message << endl;
    }

    // close two sockets
    close(s[0]);
    close(s[1]);
}