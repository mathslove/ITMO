#include <stdio.h>
#define min 1
#define max 1000
int main() {
	unsigned int x, k;
	int y, c;
	scanf("%d\n", &x);
	k = min <= x && x <= max;
	printf("%s\n", k ? "True" : "False");

	scanf("%x\n", &y);
	c = (y >> 2) & 1;
	printf("%d", c);

	return 0;
}