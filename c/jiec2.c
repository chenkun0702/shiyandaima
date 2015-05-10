#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i,j;
	int sum,t;

	for(i = 1,sum = 0;i <=5;i +=2)
	{
		for(j = 1,t = 1;j <= i; j++)
			t *= j;
		
		sum += t;
	}

	printf("sum = %d\n",sum);
	return 0;
}
