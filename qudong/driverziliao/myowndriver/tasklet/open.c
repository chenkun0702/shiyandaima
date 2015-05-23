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
	int key=0;
	int i = 0;
	fd_set  read_t;
	fd_set  write_t;
	fd = open(argv[1],O_RDWR);
	if(fd < 0)
	{
		perror("error");
		return 0;
	}
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

	while(1)
	{
		read(fd,&i,sizeof(int));
		printf("key= %d\n",i);
	}
	close(fd);
	return 0;
}
