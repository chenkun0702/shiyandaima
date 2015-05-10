#include<stdio.h>
#if 0
void fun(int b[])
{
	
	printf("%d\n",*(b + 2));
	b ++;
	printf("%d\n",*(b + 2));
}
#endif 

void fun(int *p)
{

}

int main(int argc, const char *argv[])
{
	int a[5] = {1,2,3,4,5};

	fun(a);
	return 0;
}
