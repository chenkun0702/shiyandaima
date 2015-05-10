#include<stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp;
	
	if((fp = fopen("./1.txt","r")) == NULL)
	{
		perror("fopen");
		return -1;
	}

	int ch;

	ch = fgetc(fp);
	while(feof(fp) == 0)
	{
//		ch = fgetc(fp);
		printf("%c\n",ch);
		ch = fgetc(fp);
	}
	return 0;
}
