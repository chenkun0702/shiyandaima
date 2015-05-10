#include <stdio.h>

int main(int argc, const char *argv[])
{
	int year,month,day;
	int flag = 0;
	int num = 0;

	printf("input year-month-day:\n");
	if(scanf("%d-%d-%d",&year,&month,&day) != 3)
	{
		printf("the day input error!\n");
		return -1;
	}
	
	if(year % 4 == 0 && year %100 != 0 || year % 400 == 0)
		flag = 1;
		
	switch(month)
	{
		case 2:
			if(flag)
			{
				if(day < 0 || day >29)
				{
					printf("day error1\n");
					return -1;
				}
			}
			else
			{
				if(day <0 || day >28)
				{
					printf("day error2\n");
					return -1;
				}
			}
			break ;
		case 4:
		case 6:
		case 9:
		case 11:
			if(day < 0 || day > 30)
			{
				printf("day error3\n");
				return -1;
			}
			break;
		default :
			if(day < 0 || day >31)
			{
				printf("day error4\n");
				return -1;
			}
	}
	
	switch(month)
	{
		case 12:
			num += 30;
		case 11:
			num += 31;
		case 10:
			num += 30;
		case 9:
			num += 31;
		case 8:
			num += 31;
		case 7:
			num += 30;
		case 6:
			num += 31;
		case 5:
			num += 30;
		case 4:
			num += 31;
		case 3:
			if(flag)
				num += 29;
			else
				num += 28;
		case 2:
			num += 31;
		case 1:
			num += day;
			break;
		default :
			printf("month error\n");
			return -1;
	}
	
	printf("%d %d %d is the %d day\n",year,month,day,num);
	return 0;
}
