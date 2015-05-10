#include<stdio.h>

int main(int argc, const char *argv[])
{
	int a[5];
	char *s = "hello world";

	char *p = (char *)a;

	while(*s != '\0')
	{
		*p = *s;
		s ++;
		p ++;
	}

	*p = '\0';

	printf("%s\n",(char *)a);

	*((char *)a + 1) = 'b';
	printf("%s\n",(char *)a);

	*(s + 1) = 'b';
	return 0;
}
