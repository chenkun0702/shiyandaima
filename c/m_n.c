#include <stdio.h>

int main(int argc, const char *argv[])
{
	float n = 2.0, m = 1.0;
	int i;
	float t,k,sum = 0;

	for(i = 0;i < 20;i++)
	{
		t = n / m;
		sum += t;

		k = m;
		m = n;
		n = k + m;
	}
	printf("sum = %.2f\n",sum);
	return 0;
}
