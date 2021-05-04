#include <stdio.h>
#include <stdlib.h>

int szohossz(char* szo)
{
	int index = 0, karakterszama = 0;
	while(szo[index] != '\0')
	{
		++karakterszama;
		++index;
	}
	return karakterszama;
}

int main()
{
	char* hello = "Hello World!";
	printf("%s -  Hossz: %d\n",hello,szohossz(hello));
}