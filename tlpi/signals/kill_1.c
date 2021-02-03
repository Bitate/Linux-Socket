/**
 * Demonstrate the use of Linux system call kill().
 * 
 * Ref: http://www.csl.mtu.edu/cs4411.ck/www/NOTES/signal/kill.html
 */
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>  

void sigint_handler(int);
void sigquite_handler(int);

int shm_id;
pid_t* shm_ptr;

int main(int argc, char* argv[])
{
    pid_t pid = getpid();
    key_t my_key;
    if(signal(SIGINT, sigint_handler) == SIG_ERR)
    {
        printf("SIGINT installation error!\n");
        exit(1);
    }

    if(signal(SIGQUIT, sigquite_handler) == SIG_ERR)
    {
        printf("SIGQUIT installation error!\n");
        exit(1);
    }

    my_key = ftok(".", 's');
    shm_id = shmget(my_key, sizeof(pid_t), IPC_CREAT | 0666);
    shm_ptr = (pid_t*)shmat(shm_id, NULL, 0);
    *shm_ptr = pid;

    for(int i = 0; ; ++i)
    {
        printf("From process %d: %d\n", pid, i);
        sleep(1);
    }
}

void sigint_handler(int sig)
{
    signal(sig, SIG_IGN);
    printf("From SIGINT: just got a %d (SIGINT^C) signal\n", sig);
    signal(sig, sigint_handler);
}

void  sigquite_handler(int sig)
{
     signal(sig, SIG_IGN);
     printf("From SIGQUIT: just got a %d (SIGQUIT ^\\) signal"
                          " and is about to quit\n", sig);
     shmdt(shm_ptr);
     shmctl(shm_id, IPC_RMID, NULL);

     exit(3);
}