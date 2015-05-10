#include <stdio.h>

int main(int argc, const char *argv[])
{
	char daytab[2][13] =
	{
		{0,31,28,31,30,31,30,31,31,30,31,30,31},
		{0,31,29,31,30,31,30,31,31,30,31,30,31}
	};
	
	int year,month,day;
	printf("input year month day:\n");
	if(scanf("%d %d %d",&year,&month,&day) !=3)
	{
		printf("the error");
		return -1;
	}

	int leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 ==0;
	printf("leap =%d (1:leap year)\n",leap);

	int num = 0;
	int i;
    
	if (month < 0 || month > 12 || day < 0 || day > daytab[leap][month])
	{
		printf("error\n");
		return -1;
	}

	for(i = 1;i < month;i++ )
		num += daytab[leap][i];
	num += day;

	printf("%d %d %d is the %d day\n",year,month,day,num);
	return 0;
}
