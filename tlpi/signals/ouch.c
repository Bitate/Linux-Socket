/**
 * Install a new signal handler for SIGINT.
 * 
 * Whenever you press Ctrl+C, you will see 'Ouch' :^)
 */
#include <signal.h>
#include "../lib/tlpi_hdr.h"

static void signal_handler(int signal)
{
    printf("Ouch!\n");
}

int main(int argc, char* argv[])
{
    if(signal(SIGINT, signal_handler) == SIG_ERR)
    {
        printf("error occurs\n");
        abort();
    }

    for(int i = 0; ; ++i)
    {
        printf("%d\n", i);
        sleep(3);
    }
}