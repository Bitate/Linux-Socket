#include <string.h>
#include <stdio.h>

int main()
{
	char buf[20];
	sprintf(buf, "This is demo");
	write(1, buf, strlen(buf));
}
