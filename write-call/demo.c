#include <unistd.h>
#include <string.h>


int main()
{	
	char buff[] = "this is deme";
	write(1, buff, strlen(buff));
}
