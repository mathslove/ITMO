#include <stdio.h>
#include <malloc.h>

int main() {
//Заданание 1
    float a[] = {-8.8, 11.2, 64.67, 55.32};
    float* p;

    p = a;
    for (int i = 0; i < 4; i++){
        printf("%f\n", *(p+i));
    }
    printf("\n");
//Задание 2
    float *b;

    b = (float*)malloc(4* sizeof(float));
    b[0] = -8.8;
    b[1] = 11.2;
    b[2] = 64.67;
    b[3] = 55.32;
    for (int i = 0; i < 4; i++){
        printf("%f\n", b[i]);
    }
    free(b);

    return 0;
}