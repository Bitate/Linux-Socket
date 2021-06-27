#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	printf("PID of example.c is : %d\n", getpid());
	
	pid_t pid = fork();

	if(pid == -1)
	{
		printf("fork() error\n");
	}
	
	if(pid == 0)
	{
		printf("We are in child process with PID being %d\n", getpid());
		printf("Calling hello.c from child process by execv()\n");
		char* args[] = { "Hello", "C", "Programming", NULL };
		execv("./hello.exe", args);
	}
	else
	{
		printf("We are in the parent process with PID being %d\n", getpid());
	}
	
	return 0;

}
