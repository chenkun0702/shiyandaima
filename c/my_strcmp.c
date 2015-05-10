#include <stdio.h>

int strcmp(char *a,char *b)
{
	int i;
	for(i = 0;a[i] == b[i] && a[i] != '\0' && b[i] != '\0' ;i ++)
		;
#if 0
	int i = 0;
	while(a[i] != '\0' && b[i] != '\0')
	{
		if(a[i] - b[i])
			break;
		i ++;
	}
#endif
	return a[i] - b[i];
}

int main(int argc, const char *argv[])
{
	char ss1[20] = "abcd\0";
	char ss2[20] = "abed\0";

	printf("%d\n",strcmp(ss1,ss2));
	return 0;
}
