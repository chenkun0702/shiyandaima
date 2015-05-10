#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[10][10];
	int i,j;

	for(i = 0;i < 10;i++)
	{
		for(j = 0;j <= i ;j ++)
		{
			if(j == 0 || i == j)
				a[i][j] =1;	
			else
				a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
		}
	}

	for(i = 0;i < 10;i ++)
	{
		for(j = 0;j <= i;j ++)
			printf("%3d  ",a[i][j]);
		putchar(10);
	}
	return 0;
}
