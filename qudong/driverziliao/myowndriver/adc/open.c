#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc, const char *argv[])
{
	int fd;
	char buff[128];
	int data;
	fd = open("/dev/hello",O_RDWR);
	while(1)
	{
	//	read(fd,buff,sizeof(buff));
		read(fd,&data,sizeof(int));
	//	printf("%s\n",buff);
		
		printf("%d\n",data);
			sleep(1);
	}
	return 0;
}
