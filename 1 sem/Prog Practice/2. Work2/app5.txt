#include <stdio.h>

int main(void) {
	int a[] = {88, 112, 6467, 325, 878, 3, 77, 8, 99};
	int i;
	// Задание 1
	for (i = 0; i < 9; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	// Задание 2
	int j,k;
	int b[2][2] = {1,2,3,1};
	int c[2][2] = {1,1,0,2};
	int d[2][2];

	for (i = 0; i < 2; i++){
		for (j = 0; j < 2; j++){
			for (int k = 0; k < 2; k++){
				d[i][j] += b[i][k] * c[k][j];
			}
		}
	}
	for (i = 0; i < 2; i++){
		for (j = 0; j < 2; j++){
			printf("%d ",d[i][j]);
		}
		printf("\n");
	}
	return 0;
}