#include <stdio.h>

int fun(char a[],char b[])
{
	int i,len = 0;
	for(i = 0;a[i] != '\0';i ++)
		len ++;
	for(i = 0;i < len;i ++)
	{
		b[i] = a [i];
	}
	b[len] = '\0';
	return 0;
}
int main(int argc, const char *argv[])
{
	char ss1[] = "123\0";
	char ss2[10];
	fun(ss1,ss2);
	puts(ss2);
	return 0;
}
