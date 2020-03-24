#include <stdio.h>
#include <windows.h>
int main(){
    SetConsoleOutputCP(CP_UTF8);
// Задание 3
    int x;
    char str[10];
    printf("введите число: ");
    scanf(" %d", &x);
    sprintf(str,"%d",x);
    printf("%s\n",str);
// Задание 4
    unsigned int n,k;
    unsigned int z=2;
    printf("Введите число:");
    scanf(" %d",&n);
    k=0;
    for(unsigned int i = 2; i < n+1; i++){
        for(unsigned int j = 2; j<i ;j++){
            if (i%j==0){
                k = 1;
                break;
            }
        }
        if (k==0){
            printf("%d ",i);
        }
        k=0;
    }
    return 0;
}