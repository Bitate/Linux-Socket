#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

int main()
{
    pid_t pid;
    key_t my_key;
    int shm_id;
    pid_t *shm_ptr;
    char c;
    int i;

    my_key = ftok(".", 's');
    shm_id = shmget(my_key, sizeof(pid_t), 0666);
    shm_ptr = (pid_t *)shmat(shm_id, NULL, 0);
    pid = *shm_ptr;
    shmdt(shm_ptr);

    while (1)
    {
        printf("Want to interrupt the other guy or kill it (i or k)? ");
                
        std::cin >> c;

        if(c == 'i' || c == 'I')
        {
            kill(pid, SIGINT);
            printf("Sent a SIGINT signal\n");
        }
        else if (c == 'k' || c == 'K')
        {
            printf("About to send a SIGQUIT signal\n");
            kill(pid, SIGQUIT);
            printf("Done.....\n");
            exit(0);
        }
        else
        {
            printf("Wrong keypress (%c).  Try again\n", c);
        }
    }
}