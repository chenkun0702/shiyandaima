#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i,j,n;
	int sum,jc;
	
	printf("input a num:\n");

	if(scanf("%d",&n) != 1)
	{
		printf("error\n");
		return -1;
	}
	
	for(i = 1,sum = 0,jc =1;i <= n;i ++)
	{	
		jc *= i;

		if(i % 2 ==0)
			continue;

		sum += jc;
		int m = n - 1;
		
		if(i < n && n % 2 == 1)
			printf("%d! + ",i);
		if(i < (n - 1) && n % 2 == 0)
			printf("%d! + ",i);
	}

	if(n % 2 == 1)
		printf("%d! = %d\n",n,sum);
	if(n % 2 == 0)
		printf("%d! = %d\n",n-1,sum);

	return 0;
}
