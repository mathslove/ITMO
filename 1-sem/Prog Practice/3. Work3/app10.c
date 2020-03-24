#include <windows.h>
#include <stdio.h>
#include <math.h>

void nummber_to_mass(int a[], int num, int n){
    int i=n;
    while (num>0){
        a[i--] = num%10;
        num /= 10;
    }
}

int num_sum(int a){
    if(!a)
        return 0;
    return (a % 10) + num_sum(a / 10);
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
// Задание 3
    int x,n;
    printf("Введите число и мы превратим его в массив  ");
    scanf("%d",&x);
    n = floor(log10(x))+1;
    int res[n];
    nummber_to_mass(res,x,n);
    for (int i = 1; n >= i; i++){
        printf("%d ", res[i]);
    }
    printf("\n");
// Задание 4
    int y;
    printf("Введите число и мы найдём сумму его цифр  ");
    scanf("%d",&y);
    printf("Сумма: %d", num_sum(y));
    return 0;
}