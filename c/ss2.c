#include <stdio.h>

int strcat(char *a,char *b)
{
#if 0
	int i = 0,j = 0;
	while(a[i] != '\0')
		i ++;
	while(b[j] != '\0')
		a[i ++] = b[j ++];
	a[i] = b[j];
#endif
	int i,j;
	for(i = 0;a[i] != '\0';i++)

	for(j = 0;b[j] != '\0';j++)
		a[i ++] = b [j ++];
	a[i] = a[j];


}
int main(int argc, const char *argv[])
{
	char ss1[64] = "123\0";
	char ss2[64] = "456";
	
	strcat(ss1,ss2);

	puts(ss1);
	return 0;
}
