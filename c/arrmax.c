#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[2][5] = {{5,8,5,4,6},{3,5,6,4,8}};

	int i,j,max;
	max = a[0][0];

	for(i = 0;i < 2;i ++)
	{
		for(j = 0;j < 5;j++)
		{
			if (max < a[i][j])
				max = a[i][j];
		}
	}

	for (i = 0;i < 2;i ++)
	{
		for(j = 0;j < 5;j ++)
		{
			if(max == a[i][j])
				printf("max:a[%d][%d]=%d\n",i,j,a[i][j]);
		}
	}
	
	return 0;
}
