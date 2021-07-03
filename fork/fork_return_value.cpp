#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
	pid_t pid = fork();
	
	if(pid == 0)
	{
		cout << "child process's pid is: " << getpid() << endl;
	}
	else
	{
		cout << "fork() return " << pid << " in parent process" << endl;	
	}
}
