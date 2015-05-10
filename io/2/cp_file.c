#include<stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fsrc;
	FILE *fdest;

	char buf[64];
	int ch;
	if(argc < 3)
	{
		fprintf(stderr,"usage:%s <file1> <file2>\n",argv[0]);
		return -1;
	}

	if((fsrc = fopen(argv[1],"r")) == NULL)
	{

	}

	if((fdest = fopen(argv[2],"w")) == NULL)
	{

	}
#if 0
	ch = fgetc(fsrc);

	while(feof(fsrc) == 0)
	{
//		ch = fgetc(fsrc);
		fputc(ch,fdest);
		ch = fgetc(fsrc);
	}
#endif 
#if 0
	while(fgets(buf,sizeof(buf),fsrc) != NULL)
	{
		fputs(buf,fdest);
	}
#endif 
	size_t n;

	while((n = fread(buf,1,sizeof(buf),fsrc)) > 0)
	{
		fwrite(buf,1,n,fdest);
	}
	
	fclose(fsrc);
	fclose(fdest);
	return 0;
}
