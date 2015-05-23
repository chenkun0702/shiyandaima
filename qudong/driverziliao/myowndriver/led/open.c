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
	int i=0;
	fd_set  read_t;
	fd_set  write_t;
	fd = open("/dev/helllo-0",O_RDWR);
	if(fd < 0)
	{
		perror("error");
		return 0;
	}
	while(1)
	{
		FD_ZERO(&read_t);
		FD_ZERO(&write_t);
		FD_SET(fd,&read_t);
		FD_SET(fd,&write_t);
		select(fd+1,&read_t,&write_t,NULL,NULL);

		if(FD_ISSET(fd,&read_t))
		{
			printf("read\n");
			sleep(1);
		}
		if(FD_ISSET(fd,&write_t))
		{
			printf("write\n");
			sleep(1);
		}
	}

	write(fd,buff,20);
	ret=read(fd,buff,sizeof(buff));
	while(1)
	{
		ioctl(fd,LED_ON,&i);
		sleep(1);
		ioctl(fd,LED_OFF,&i);
		sleep(1);
		i++;
		if(i >= 4)
			i=0;
	}
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
