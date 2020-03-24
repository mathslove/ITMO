#define _CRT_SECURE_NO_WARNINGS//сэйф ввод, без него ошибка
#include <stdio.h>
int main() {
	char line[80];
	float a;

	scanf("%s\n", line);
	printf("%s\n", line);
	scanf("%f\n", &a);
	printf("%f\n", a);
	return 0;
}