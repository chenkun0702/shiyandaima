#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[2][3] ={{1,2,3},{4,5,6}};
	int b[3][2];
	int i,j;

	printf("原数组元素：\n");
	for(i = 0;i < 2;i ++)
	{
		for(j = 0;j < 3; j++)
		{
			printf("%d ",a[i][j]);
		
			b[j][i] = a[i][j];
		}
		putchar(10);
	}
	putchar(10);
	printf("转换后数组元素：\n");
	for(j = 0;j< 3;j ++)
	{
		for(i = 0;i < 2;i ++)
		{
			printf("%d ",b[j][i]);
		}
		putchar(10);
	}
	putchar(10);
	return 0;
}
