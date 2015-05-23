#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/ioctl.h>
#include"head.h"
int main(int argc, const char *argv[])
{
	char buff[20] = "hello write";
	int fd;
	int ret;
	fd = open("/dev/helllo-0",O_RDWR);
	if(fd < 0)
	{
		perror("error");
		return 0;
	}

	write(fd,buff,20);
	ret=read(fd,buff,sizeof(buff));
	ioctl(fd,LED_ON);
	printf("LED_ON\n");
	ioctl(fd,LED_OFF);
	printf("LED_OFF\n");

	if(ret < 0)
	{
		perror("error num");
		return 0;
	}
	
	printf("buff = %s\n",buff);
	sleep(20);
	close(fd);
	return 0;
}
