#include<stdio.h>

int main(int argc, const char *argv[])
{
	int ch;

//	char ch;
	ch = fgetc(stdin);

	printf("%x\n",ch);
	return 0;
}
