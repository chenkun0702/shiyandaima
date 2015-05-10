#include <stdio.h>
#include <math.h>
int main(int argc, const char *argv[])
{
	float a,b,c,area,s;
	
	if(scanf("%f%f%f",&a,&b,&c) != 3 || a + b <= c || a + c <= b || b + c <= a)
	{
		printf("error\n");
		return -1;
	}
	
	s = 1.0 / 2 * (a + b + c);
	area = sqrt(s * (s - a) * (s - b) * (s - c));
	printf("a = %7.2f,b = %7.2f,c = %7.2f,\ns = %7.2f,\narea = %7.2f\ni",a,b,c,s,area);
	return 0;
}
