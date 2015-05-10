#include <stdio.h>

int main(int argc, const char *argv[])
{
	char ch;
	ch = getchar();

	int i,j;

	for(i = 1;i <= ch - 'A' +1;i ++)
	{
		for(j = 1;j <= 2 * i - 1; j ++)
		{
			if(j < i)
				putchar('_');
			else
				putchar(ch -(j - i));
		}
		putchar(10);
	}
	return 0;
}
