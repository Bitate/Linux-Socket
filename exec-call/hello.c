#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("We are in hello.c and PID is: %d\n", getpid());
	return 0;
}
