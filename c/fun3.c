#include<stdio.h>

void fun(int a,int b)
{
	printf("a = %d,b = %d\n",a,b);

}

int main(int argc, const char *argv[])
{
	int a = 10,b = 20;

	fun(a,b);

	void (*p)(int,int) = fun;

	(*p)(a,b);
	p(a,b);


	int add = (int)fun;

	((void (*)(int,int))add)(a,b);
	return 0;
}
