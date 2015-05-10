#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i,j,k;
	char ch;
	ch = getchar();
	for(i = 1;i <= ch - 'A' + 1;i++)
	{
		for(j = i - 1;j > 0;j--)
			putchar('_');
		for(k = i;k > 0; k--)
			putchar(ch - (i - k));
		putchar(10);
	}
	return 0;
}
