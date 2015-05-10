#include <stdio.h>

int main(int argc, const char *argv[])
{
	char c ;
	c = getchar();

	if(c >= 'A' && c <= 'Z')
		c = c + 'a' -'A';
	else if(c >= 'a' && c <= 'z')
		c = c - ('a' - 'A');
	else if(c >= '0' && c <= '9')
		printf("number:");
	else
		printf("other:");
	
	putchar(c);
	putchar('\n');
	
	return 0;
}
