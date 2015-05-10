#include <stdio.h>

int main(int argc, const char *argv[])
{
	int num;
	int sumi = 0,sumj = 0;
	int i = 0,j = 0; //even_ct  even_sum  odd_ct

	printf("input number:\n");

	while((scanf("%d",&num) == 1) && num != 0)
	{
		if(num % 2 == 0)
		{
			i ++;
			sumi = sumi + num;
		}
		if(num % 2 == 1)
		{
			j ++;
			sumj = sumj + num;
		}

	}
	
    if(i != 0 )
		printf("even:i = %d,ai = %.2f\n",i,(float)(sumi / i));
	if(j != 0)
		printf("odd :j = %d,aj = %.2f\n",j,(float)(sumj / j));
	return 0;
}
