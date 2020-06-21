#include <time.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    // status of socket operations
    int status;
    // a pair of connected sockets
    int s[2];
    // message to read/write
    string message;
    char buffer[80];

    // create socket pair
    status = socketpair(AF_LOCAL, SOCK_STREAM, 0, s);
    if(status == -1)
    {
        cout << "Can not create socket pair" << endl;
        exit(1);
    }

    // child pid, here refers to client
    pid_t childPID = fork();
    if( childPID == (pid_t) - 1)
    {
        cout << "Failed to fork int two processes" << endl;
        exit(1);
    }
    else if (childPID == 0)
    {
        // successfully create child process (here refers to client)
        char recvBuffer[80];
        cout << "Parent PID is : " << (long)getppid() << endl;

        // server uses s[1], ignore s[0]
        close(s[0]);
        s[0] = 01;

        // generate message
        message = "%A %d-%b-%Y %l:%M %p";
        
        // write to server
        status = write(s[1], message.c_str(), message.size());
        if(status < 0)
        {
            cout << "Failed to write to server" << endl;
            exit(1);
        }
        cout << "Client send : " << message << endl;

        // we will not write to server anymore.
        if( shutdown(s[1], SHUT_WR) == -1)
        {
            cout << "Failed to shutdown socket for writing" << endl;
            exit(1);
        }

        // receive reply from server.
        status = read(s[1], recvBuffer, sizeof(buffer));
        if(status < 0)
        {
            cout << "Failed to receive from server" << endl;
            exit(1);
        }

        close(s[1]);
    }
    else
    {
        // This is the parent process (server)
        int status;
        char buffer[80];
        time_t time;

        cout << "Child PID is : " << (long)childPID << endl;

        close(s[1]);
        s[1] = -1;

        // wait for request from client
        status = read(s[0], buffer, sizeof(buffer));
        if(status < 0)
        {
            cout << "Failed to read from client" << endl;
            exit(1);
        }

        // process the received message
        cout << "server receive : " << buffer << endl;

        // send back the response to client
        status = write(s[0], buffer, sizeof(buffer));
        if(status < 0)
        {
            cout << "Failed to write back to client" << endl;
            exit(1);
        }
        else
        {
            close(s[0]);

            // wait for child process to exit.
            waitpid(childPID, &status, 0);
        }
        
    }
    
    
}