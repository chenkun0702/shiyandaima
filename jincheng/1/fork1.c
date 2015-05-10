#include<stdio.h>
#include<unistd.h>

int main(int argc, const char *argv[])
{
	pid_t pid;
	int i = 10;
	pid = fork();

	printf("%d\n",pid);
	if(pid == -1)
	{
		perror("fork");
		return -1;
	}

	else if(pid == 0)
	{
		printf("child\n");
		i ++;
		printf("i = %d\n",i);
		while(1);
	}
	else 
	{
		sleep(1);
		printf("father\n");
		i ++;
		printf("i = %d\n",i);
		while(1);
	}
	return 0;
}
