#include<stdio.h>

int main(int argc, const char *argv[])
{
	int count;

	for(count = 0;;count ++)
	{
		printf("%0128d",count);
		usleep(100000);
	}
	return 0;
}
