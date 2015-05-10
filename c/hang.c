#include <stdio.h>

int main(int argc, const char *argv[])
{
	char ch,ch1;
	int i,j,n;

	printf("input :\n");
	ch = getchar();
	ch1 = ch;
	n = ch -'A' + 1;

	for (i = 1;i <= n;i++)
	{
	
		ch = ch1; 
		for(j = 0;j < i;j++)
		{
			putchar(ch);
			ch = ch - 1 ;
		}
		putchar('\n');
	}
	return 0;
}
