#include<stdio.h>

int main(int argc, const char *argv[])
{
	int a[5] = {1,2,3,4,5};

	int *p = (int *)(&a + 1);

	printf("%d\n",*(p - 1));
	return 0;
}
