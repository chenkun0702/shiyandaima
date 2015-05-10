#include<stdio.h>
#if 0
void fun(int a[][3])
{

}
#endif 
void fun(int (*p)[3])
{

}
int main(int argc, const char *argv[])
{
	int a[2][3];


	fun(a);
	return 0;
}


char *str[3];

fun(str);

void fun(char *str[])
void fun(char **p)
