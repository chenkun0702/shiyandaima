#include <stdio.h>
int main(int argc, const char *argv[])
{
	int x,y;
	
	printf("x = ");
	scanf("%d",&x);
	if(x > 0 && x <= 10)
	{
		y = 2 * x + 1;
	
	}
	else if(x > 10)
	{
		y = 2 * x - 1;
		
	}
	else
	{
		y = 0;
	}
		
		printf("y = %d\n",y);
	return 0;
}
