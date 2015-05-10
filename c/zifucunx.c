#include<stdio.h>

int main(int argc, const char *argv[])
{
	char instring[50];
	int i,len = 0;
	scanf("%s",instring);
	char outstring[50];
	for(i = 0;instring[i] != '\0';i ++)
		len ++;
	for(i = 0;i < len;i ++)
		outstring[i] = instring[len - 1 - i ];
	outstring[len] = '\0';
	printf("%s\n",outstring);
//	printf("%dkkkkk \n",outstring[len + 2]);
	return 0;
}
