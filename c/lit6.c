#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[] = {5,8,7,6,2,7,3};
	int y,*p = &a[1];
	y = (*--p) ++;
	printf("%d",y);
	printf("%d",a[0]);

	return 0;
}
