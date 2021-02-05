#define POSIXC_SOURCE 199309
#define __USE_POSIX199309

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char *argv[])
{
    union sigval sv;
    if (argc < 4 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pid signal-num data [num-sigs]\n", argv[0]);
    
    /* 
     * Display our PID and UID, so that they can be compared with the
     * corresponding fields of the siginfo_t argument supplied to the
     * handler in the receiving process 
     */
    printf("%s: PID is %ld, UID is %ld\n", argv[0],
           (long)getpid(), (long)getuid());

    int signal = getInt(argv[2], 0, "signal-num");

    int signal_value = getInt(argv[3], GN_ANY_BASE, "data");

    int signal_numbers = (argc > 4) ? getInt(argv[4], GN_GT_0, "num-sigs") : 1;

    for (int j = 0; j < signal_numbers; j++)
    {
        sv.sival_int = signal_value + j;
        if (sigqueue(getLong(argv[1], 0, "pid"), signal, sv) == -1)
            errExit("sigqueue %d", j);
    }

    exit(EXIT_SUCCESS);
}

