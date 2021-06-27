#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

int main()
{
	pid_t pid = fork();

	if(pid == -1)
	{
		cout << "can't fork" << endl;
		exit(1);
	}
	else if(pid == 0)
	{
		cout << "This is child process with PID being " << getpid() << endl;
		for(int i = 0; i < 10; ++i)
			cout << "child is counting " << i << endl;
		exit(0);
	}
	else
	{
		cout << "This is parent process" << endl;
		cout << "Waiting for child to finish" << endl;
		int status;
		pid_t finish_pid = wait(&status);
		cout << "PID: " << finish_pid << " has finished job, parent is about to exit" << endl;
		exit(0);
	}
}	
