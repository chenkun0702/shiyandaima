#include <stdio.h>

int main(int argc, const char *argv[])
{
	char ch;
    printf("input:\n");
	while((ch = getchar()) != '\n')
	{
//    	printf("&");
		if(ch >= 'x' && ch <= 'z' || ch >= 'X' && ch <= 'Z')
			ch = ch - 26 +3;
		else if(ch >= 'a' && ch <= 'w' || ch >= 'A' && ch <= 'W')
			ch = ch + 3;
		else
			;
		putchar(ch);
		
	}
	putchar('\n');
	return 0;
}
