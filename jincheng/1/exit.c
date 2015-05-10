#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, const char *argv[])
{
	printf("hello");
//	exit(0);
	_exit(3);
	printf("world\n");
}
