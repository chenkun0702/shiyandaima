#include <stdio.h>

#define maroc(y) do{if(y == 1) function();}while(0);

void function(void)
{
	printf("hello\n");
}

int main(int argc, const char *argv[])
{
	int x,y;
	x = 1;
	y = 1;

	if(x = 1)
		maroc(y)
	else
		printf("worle\n");
	return 0;
}
