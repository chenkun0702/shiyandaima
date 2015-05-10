#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main(int argc, const char *argv[])
{
	pid_t pid;
	int status;
	pid = fork();

	if(pid == -1)
	{

	}
	else if(pid == 0)
	{
		sleep(1);
		printf("child\n");
		exit(2);
//		while(1);
	}
	else 
	{
		printf("abcd\n");
//		wait(NULL);
		wait(&status);

		printf("father\n");
		printf("status = %x\n",status);
		while(1);
	}
//	while(1);
	return 0;
}
