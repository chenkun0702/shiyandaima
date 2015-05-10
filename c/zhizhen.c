#include <stdio.h>

int main(int argc, const char *argv[])
{
	int *p1,*p2,a,b;
	p1 = &a,p2 = &b;
	a = 1,b = 20;
	printf("p1 = 0x%x, p2 = 0x%x\n",p1,p2);
	printf("p1 = %p,p2 = %p\n",p1,p2);
	printf("p1 = %u,p2 = %u\n",p1,p2);

	return 0;
}
