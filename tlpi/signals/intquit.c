/**
 * Create a signal handler for SIGINT and SIGQUIT.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void signal_handler(int signal)
{
    static int count = 0;

    if(signal == SIGINT)
    {
        ++count;
        printf("Caught SIGINT (%d)\n", count);
        return;
    }
    else // must be SIGQUIT
    {
        printf("Caught SIGQUIT - Goodbye!\n");
        exit(0);
    }
}

int main(int argc, char* argv[])
{
    if(signal(SIGINT, signal_handler) == SIG_ERR)
        exit(0);
    if(signal(SIGQUIT, signal_handler) == SIG_ERR)
        exit(0);
    
    for(;;)
        pause(); // block until a signal gets caught
}