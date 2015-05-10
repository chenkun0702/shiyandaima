#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[5] ={97,15,27,5,35};
	int i,j,min,temp,index;
	for(i = 0;i < 4;i ++)
	{
		min = a[i];
		index = i;
		for(j = i + 1;j < 5;j++)
		{
			if(min > a[j])
			{
				min = a[j];
				index = j;
			}
		}

		
		temp = a[index];
		a[index] = a [i];
		a[i] = temp;

	
		
	}
	for(i = 0;i < 5;i ++)
		printf("%d ",a[i]);
	putchar(10);
	return 0;
}
