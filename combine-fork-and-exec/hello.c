#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	printf("We are in hello.c with PID being %d\n", getpid());
	for(int i = 0 ; i < argc; ++i)
	{
		printf("arg %d is %s\n", i, argv[i]);
	}
	return 0;
}
