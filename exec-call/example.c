#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	printf("PID of example.c is %d\n", getpid());
	char* args[] = { "Hello", "C", "Programming", "Under", "Linux", "OS", NULL };
	execv("./hello.exe", args);
	printf("Back to example.c\n"); // this line will never get executed
	return 0;
}
