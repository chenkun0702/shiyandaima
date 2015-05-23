#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/ioctl.h>
#include"head.h"
#include<signal.h>
int i =0;
int fd;
void func(int a)
{

	read(fd,&i,sizeof(int));
	printf("****************\n");
	printf("key= %d\n",i);
}
int main(int argc, const char *argv[])
{
	char buff[20] = "hello write";
	int ret;
	int key=0;
	int flags;
	fd_set  read_t;
	fd_set  write_t;
	fd = open(argv[1],O_RDWR);
	if(fd < 0)
	{
		perror("error");
		return 0;
	}
#if 0
	while(1)
	{
		read(fd,&key,sizeof(int));
		if(key == 1 || key == 2 || key==3 | key == 4)
		
		{
			i = key;
			ioctl(fd,LED_ON,&i);
		
		}
		if(key == 6)
		{
			ioctl(fd,LED_OFF,&i);

		}
		if(key == 7)
		{
			printf("break");
			return 0;
		}
	}
	if(ret < 0)
	{
		perror("error num");
		return 0;
	}
#endif
	signal(SIGIO,func);
	fcntl(fd,F_SETOWN,getpid());
	flags = fcntl(fd,F_GETFL);
	fcntl(fd,F_SETFL,flags|FASYNC);
	while(1)
	{
		sleep(10000000);
	}
	close(fd);
	return 0;
}
