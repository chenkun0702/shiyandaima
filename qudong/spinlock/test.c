#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>

#include "hello.h"

int main(int argc, const char *argv[])
{
	int fd;
	char buf[1024] = "Hello World"; 

	fd = open("/dev/hello", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	sleep(10);
	
	close(fd);

	return 0;
}
