#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i,j,sum;
	for(i = 1;i <= 1000;i++)
	{
		for(j = 1,sum = 0; j <= i / 2;j++)
		{
			if(i % j == 0)
				sum += j;
		}
		
		if(sum == i)
			printf("%d ",i);
	}
	putchar('\n');
	return 0;
}

