#include<stdio.h>

void (*fun(int,void(*)(int)))(int);
void fun1(int);
int main(int argc, const char *argv[])
{
	void (*(*p)(int,void(*)(int)))(int);

	p = fun;

	p(100,fun1);
	return 0;
}

void fun1(int nu)
{
	printf("nu = %d\n",nu);
}

void (*fun(int nu,void (*p_fun)(int)))(int)
{
	p_fun(nu);

	return p_fun;
}
