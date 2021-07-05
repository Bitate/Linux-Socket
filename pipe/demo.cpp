#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

#define MAX_BUFFER_SIZE 100

int main()
{
	int pipefds[2];
	pipe(pipefds);

	pid_t fork_result = fork();

	if(fork_result < 0)
	{
		cout << "fork error" << endl;
		exit(EXIT_FAILURE);

	}
	else if(fork_result == 0) 
	{
		// child writes
		close(pipefds[0]);
		
		char buffer[] = "data";

		write(pipefds[1], &buffer, 5);

		cout << "child writes" << endl;

		close(pipefds[1]);
	}
	else
	{
		// parent reads
		wait(NULL);

		close(pipefds[1]);
		
		char buffer[MAX_BUFFER_SIZE];	
		
		read(pipefds[0], buffer, MAX_BUFFER_SIZE);
		
		close(pipefds[0]);
		
		cout << "parent reads: " << buffer << endl;
	}
}	
