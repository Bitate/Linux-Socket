/**
 * @brief Fork a press demo
 */
int child_process;
if((child_process = fork()) == 0)
{
    // I'm a child now :)
    // Let's do something child-ish.

    exit(status);   // This is important!
}
else if (child_process > 0)
{
    // I'm a parent now :(
    // Alright, I'm do something parent-ish.
    int retval;

    // ...

    wait(&retval); // wait child's end

}
else
{
    // Error happens
    perror("Tried to fork() a process");
}


/**
 * @brief Job-delegation style of multitasking.
 */
int child_process;
for(;;) // Infinite loop
{
    // Wait for job request
    // ...

    if((child_process = fork()) == 0)
    {
        // I'm child :)
        // process the request
        exit(status);
    }
    else if(child_process > 0)
    {
        // I'm parent :(
        // Clean up 
        // Don't use wait(), use signals instead.
    }
    else if (child_process < 0)
    {
        // Error
        perror("Can't process job request");
    }
}


/**
 * @brief Forking without differentiation demo.
 *      This is a demo of "running together",
 *      which means multitasking without differentiation.
 *      If fork() is called without some differentition,
 *      the two tasks duplicate each other's work, 
 *      thus wasting CPU time.
 */
// Do something 
// ...

fork();

// continue
// ...


/**
 * @brief Process creation demo
 */
void child_process_function()
{
    // do something child-ish
}

int main()
{
    int child_process;

    // create new process
    if((child_process = fork()) < 0)
        perror("Fork error");
    else if (child_process == 0)
    {
        // I'm child
        child_process_function();
        exit(0);
    }
    else if (child_process > 0)
    {
        // I'm parent
        // do something parent-ish

        // wait for child to end
        wait();
    }

    return 0;
}


/** 
 * @brief Thread creation by using pthread.h libray demo
 */
#include <pthread.h>

void *child_process_function()
{
    //
}

int main()
{
    thread_t child_thread;
    if( pthread_create(&child_thread, NULL, &child_thread_function, &arg) != 0)
        perror("create thread error");
    // threads don't have a child section
    // we are implicitly still in the parent thread.
    // do some other work
    // wait for child to end
    pthread_join(child_thread, NULL);
    return 0;
}