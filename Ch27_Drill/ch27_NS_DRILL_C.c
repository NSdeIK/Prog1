#include <stdio.h>

void func(char* p, int x)
{
	printf("\np is \"%s\" and x is %i \n",p,x);
}

int main()
{
	printf("Hello World!\n");

	char* hello = "Hello";
	char* world = "World!";

	func("foo",7);
	func("why?", 100);

	printf("\n%s %s\n",hello,world);
}