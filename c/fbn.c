#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i,m,n,t;
	m = 1,n = 1;
	printf("%d %d ",m,n);

	for (i = 3;i <= 10; i ++)
	{
		t = m + n;
		
		printf("%d ",t);
		n = m;
		m = t;

	}
	putchar(10);
	return 0;
}



