#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "head.h"
#include <sys/ioctl.h>
int main(int argc, const char *argv[])
{
	
	int fd;
	char buff[30] = "hello world";

	fd  = open("/dev/atomic",O_RDWR);
	if(fd  <  0)
	{
		perror("fail open");
		return -1;
	}

	//write(fd,buff,20);
	//
	//ioctl(fd,LED_ON);
	//ioctl(fd,LED_OFF,&fd);


	sleep(10);

//	read(fd,buff,1024);

//	printf("buff  = %s\n",buff);

//	read(fd,buff,sizeof(buff));
//	printf("buff  = %s\n",buff);

//	sleep(3);


//	while(1);
	close(fd);
	return 0;
}
