#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[2][4] ={{0xbff9aed8,101,102,103},{110,111,112,113}};
	int **pp;
	pp = **a;
	
	printf("&a[1][3]:%p **p = %ld\n ",&a[1][3],**pp);

	return 0;
}
