#include<stdio.h>

int main(int argc, const char *argv[])
{
	int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

	int (*p)[3] = a;
	printf("a + 1 = %p\n",a + 1 + 1);
	printf("&a[1] = %p\n",&a[1] + 1);

	printf("a[1] = %p\n",a[1] + 1);
	printf("*(a + 1) = %p\n",*(a + 1) + 1);


	printf("%d\n",*(*(a + 2) + 1));
	
	printf("%d\n",*((int *)((int)a + 3 * 4 + 4)));
	return 0;
}

