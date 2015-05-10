#include <stdio.h>

int main(int argc, const char *argv[])
{
	int n,i,j,t;
//	int a[10] = {12,25,36,14,89,32,65,75,2,19};
	int a[10];

	for(i = 0;i < 10;i ++)
	scanf("%d",&a[i]);

//	for(i = 0;i < 10;i ++)
//		printf("%d ",a[i]);
//		putchar(10);
	for(i = 0;i < 9 ;i ++)
	{
		for(j = 0;j < 9 - i;j ++) //上限不能超过数组边界
		{
			if(a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
//		printf("%d ",a[9-i]);
	}
	for(i = 0;i < 10;i ++)
		printf("%d ",a[i]);

	putchar(10);
	return 0;
}
