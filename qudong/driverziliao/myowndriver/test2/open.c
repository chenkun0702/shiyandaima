#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/ioctl.h>
#include<signal.h>
#include"head.h"
char buff[20] = "hello write";
int fd;
void func(int num)
{
	printf("num = %d\n",num);
	read(fd,buff,sizeof(buff));
	printf("receive signal%s\n",buff);
}
int main(int argc, const char *argv[])
{
	int flag = 0;
	int i = 0;
	int ret;
	fd_set  read_t;
	fd_set  write_t;
	fd = open("/dev/helllo-0",O_RDWR);
	if(fd < 0)
	{
		perror("error");
		return 0;
	}
#if 0
	signal(SIGIO,func);//将SIGIO和函数FUNC关联起来
	fcntl(fd,F_SETOWN,getpid());//将当前进程和文件描述符关联起来，没有此步内核不知道将信号发给哪个进程
	flag = fcntl(fd,F_GETFL);//获取文件状态标志
	fcntl(fd,F_SETFL,flag|FASYNC);//启用异步通知机制
	sleep(2000);
 
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
#endif
//	write(fd,buff,20);
	ret=read(fd,buff,sizeof(buff));
	while(1)
	{
		ioctl(fd,LED_ON,&i);
		sleep(1);
		ioctl(fd,LED_OFF,&i);
		sleep(1);
		i++;
		if(i >=4)
			i = 0;
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
