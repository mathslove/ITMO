#include <stdio.h>
#include <math.h>
int main()
{
	float a;
	float z1;
	float z2;
	scanf("%f", &a);
	printf("a=%f\n", a);
	z1 = (sin(2 * a) + sin(5 * a) - sin(3 * a)) / (cos(a) + 1 - 2 * (pow(sin(2 * a), 2)));
	printf("z1=%f\n", z1);
	z2 = 2 * (sin(a));
	printf("z2=%f\n", z2);
	return 0;
}