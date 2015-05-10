#include <stdio.h>

int main(int argc, const char *argv[])
{
	int score;

	if(scanf("%d",&score) != 1)
	{
		printf("error\n");
		return -1;
	}

	if(score < 0 || score > 100)
	{
		printf("error1\n");
		return -1;
	}

	if(score < 90)
	{
		if(score < 80)
		{
			if(score <70 )
			{
				if(score < 60)
				{
					puts("No pass");
				}
				else
					puts("D");
			}
			else
				puts("C");
		}
		else
			puts("B");
	}
	else
		puts("A");

	return 0;
}
