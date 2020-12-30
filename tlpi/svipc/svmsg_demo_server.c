/**
 * Cleanup of IPC objects within a server
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>

#include "tlpi_hdr.h"

#define KEY_FILE "input.txt"

int main(int argc, char* argv[])
{
    int msqid;
    key_t key;
    const int MQ_PERMS = S_IRUSR | S_IWUSR | S_IWGRP;   // rw--w----

    // Generate the key for message queue
    key = ftok(KEY_FILE, 1);
    if(key == -1)
        printf("Cannot generate key for message queue");
    
    // while msgget() fails, try creating the queue exclusively
    while( (msqid = msgget(key, IPC_CREAT | IPC_EXCL | MQ_PERMS)) == -1)
    {
        if(errno = EEXIST)
        {
            msqid = msgget(key, 0);
            if(msqid == -1)
                errExit("msgget() failed to retrieve old queue ID");
            if(msgctl(msqid, IPC_RMID, NULL) == -1)
                errExit("msgget() failed to delete old queue");
            printf("Removed old message queue (id=%d)\n", msqid);
        }
        else // Some other error, exit
        {
            errExit("msgget() failed");
        }
        
    }
    // After the loop, we've successfully created the message queue,
    // so that we can carry on to do the work :)
    exit(EXIT_SUCCESS);
}