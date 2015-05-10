#include<stdio.h>

#include<unistd.h>

int main(int argc, const char *argv[])
{
//	execl("/bin/ls","ls","-l",NULL);

//	char *const str[] = {"ls","-l",NULL};

//	execv("/bin/ls",str);

	execlp("ls","ls","-l",NULL);
	return 0;
}
