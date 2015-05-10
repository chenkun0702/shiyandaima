#include <stdio.h>
#define N 20
int main(int argc, const char *argv[])
{
#if 0
	char s1[N];
	printf(">");

	scanf("%s",s1);

	printf("%s\n",s1);
#endif
	char s[N];
	int i = 0;
	while(scanf("%s",s) != EOF)
	{
		printf("> i=%d,s=%s***\n", ++ i,s);
	}
	return 0;
}
