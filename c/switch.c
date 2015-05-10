#include <stdio.h>

int main(int argc, const char *argv[])
{
	while(1)
	{
		int i;
		long long int a,sum;
		printf("____________________\n");
		printf("*******1_show*******\n");
		printf("*******2_add********\n");
		printf("*******3_clear******\n");
		printf("*******0_quit*******\n");
		printf("Please input a: number:\n");
		sum = 1000;
		scanf("%d",&i);
		
		if(i <0 || i >4)
			printf("error!\nPlease input a right number!\n");
		
		switch(i)
		{
			case 1:
				printf("sum = %lld\n",sum);
				break;
			case 2:
				printf("Please input the adder:\n");
				scanf("%lld",&a);
				sum += a;
			    printf("sum = %lld\n",sum);
				break;
			case 3:
				sum = 0;
				printf("sum = %lld\n",sum);
				break;
			case 0:
				return 0;

		}
	}
	return 0;
}
