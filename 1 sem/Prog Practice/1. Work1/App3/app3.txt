#include <stdio.h>

int main(void) {
	int x;
	int y;
	
	printf("1. ¬ведите число в 16-ричной системе = \n");
	scanf("%x\n",&x);
	
	printf("2. „исло в 8-ричной = %o\n", x);
	
	printf("3. „исло в 8-ричной %o и это же число со сдвигом на 3 влево = %o\n",x, x << 3);
	
	printf("4. „исло в 8-ричной %o,число в инверсии %o\n", x, ~x);
	
	printf("5. ¬ведите число в 8-ричной дл€ побитовой XOR = \n");
	scanf("%o\n", &y);
	printf("   1ое число XOR 2ое = %o\n", x ^ y);
	
	return 0;
}
