#include<stdio.h>

int main(int argc, const char *argv[])
{
	char *str[3] = {"abc","def","123"};
	char **p = str;

	
	printf("%s\n",*(p + 1));
	printf("%c\n",*(*(p + 1) + 1));
	return 0;
}

//char *str[3] = {a的地址，d的地址，1的地址}
