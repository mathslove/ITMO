#include <cmath>
#include "add.h"

void func1(int* x, int* y)
{
    if (*x > *y){
        *x = *x % *y;
    } else if (*y > *x) {
        *y = *y % *x;
    }
}

void func1(int& x, int& y){
    if (x > y){
        x = x % y;
    } else if (y > x) {
        y = y % x;
    }
}
//----------------------
void func2(float* x){
    *x = round(*x);
}

void func2(float& x){
    x = round(x);
}
//----------------------
void func3(float* x, int y){
    *x -= y;
}

void func3(float& x, int y){
    x -= y;
}
//----------------------
void func41(int a[3][3]){
    int temp;
    for (int i = 0; i < 3; i++){
        for(int j = i; j < 3; j++){
            temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
        }
    }
}

void func42(int (&a)[3][3]){
    int temp;
    for (int i = 0; i < 3; i++){
        for(int j = i; j < 3; j++){
            temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
        }
    }
}
