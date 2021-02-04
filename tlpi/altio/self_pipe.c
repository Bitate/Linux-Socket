#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/select.h>

#ifndef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
#endif

// for pipe
static int pfd[2];

static void handler(int sig)
{
    int saved_error = errno;
    if (write(pfd[1], "x", 1) == -1 && errno != EAGAIN)
        exit(1);
    errno = saved_error;
}

int main(int argc, char *argv[])
{
    fd_set read_fds;
    int ready, nfds, flags;
    struct timeval timeout;
    struct timeval *pto;
    struct sigaction signal_action;
    char ch;
    /* ... Initialize 'timeout', 'read_fds', and 'nfds' for select() */
    if (pipe(pfd) == -1)
        exit(1);

    FD_SET(pfd[0], &read_fds);     /* Add read end of pipe to 'read_fds' */
    nfds = max(nfds, pfd[0] + 1);  /* And adjust 'nfds' if required */
    flags = fcntl(pfd[0], F_GETFL);
    if (flags == -1)
        exit(1);
    flags |= O_NONBLOCK; /* Make read end nonblocking */
    if (fcntl(pfd[0], F_SETFL, flags) == -1)
        exit(1);
    flags = fcntl(pfd[1], F_GETFL);
    if (flags == -1)
        exit(1);
    flags |= O_NONBLOCK; /* Make write end nonblocking */
    if (fcntl(pfd[1], F_SETFL, flags) == -1)
        exit(1);
    sigemptyset(&signal_action.sa_mask);
    signal_action.sa_flags = SA_RESTART; /* Restart interrupted read()s */
    signal_action.sa_handler = handler;
    if (sigaction(SIGINT, &signal_action, NULL) == -1)
        exit(1);
    while ((ready = select(nfds, &read_fds, NULL, NULL, pto)) == -1 &&
           errno == EINTR)
        continue;    /* Restart if interrupted by signal */
    if (ready == -1) /* Unexpected error */
        exit(1);
    if (FD_ISSET(pfd[0], &read_fds))
    { /* Handler was called */
        printf("A signal was caught\n");
        for (;;)
        { /* Consume bytes from pipe */
            if (read(pfd[0], &ch, 1) == -1)
            {
                if (errno == EAGAIN)
                    break; /* No more bytes */
                else
                    exit(1); /* Some other error */
            }
            /* Perform any actions that should be taken in response to signal */
        }
    }
    /* Examine file descriptor sets returned by select() to see
which other file descriptors are ready */
}