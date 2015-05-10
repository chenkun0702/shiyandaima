#include<stdio.h>

//void fun(int);//函数的声明

void fun(int *p)
{

}


int main(int argc, const char *argv[])
{
	int a = 10;

//	fun(a); //函数的调用，a叫做实参
	
	fun(&a);
	return 0;
}
#if 0
void fun(int a)//函数的定义
{
	
}
#endif 
