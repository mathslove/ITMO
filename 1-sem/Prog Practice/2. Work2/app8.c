#include <windows.h>

#include <stdio.h>
#include <string.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);

// Задание 3
    char line1[50], line2[50];
    int comp;
    gets(line1);
    gets(line2);
    comp = strncmp(line1,line2,100);
    if (comp>0){
        printf("Строка 1 больше");
    } else if (comp<0){
        printf("Строка 2 больше");
    }
    else{
        printf("Строки равны");
    }
    printf("\n");
// Задание 5
    char str1[50],str2[50];
    printf("Введите копируемую строку и изменяемую \n");
    gets(str1);
    gets(str2);
    strcpy(str2,str1);
    printf("Вывод первой строки: %s второй: %s\n",str1,str2);
// Задание  7
    char str[50];
    unsigned int n;
    printf("Введите строку, а мы скажем вам её длину\n");
    gets(str);
    n = strlen(str);
    printf("Длина строки:%d",n);
// Задание 9
    int k1;
    char c[10],s[50];
    printf("Введите строку и символ для которого хотите найти псоледние  вхождение\n");
    gets(s);
    gets(c);
    for (int i=strlen(s)-1; i>=0 ;i--){//идём по строке
        if (s[i]==*c) {
            k1=i;
            break;
        }//если символ найден то взять его номер
    }
    printf("Индекс последнего вхождения символа равен:%d ",k1);
// Задание 11
    int k2=0;
    char s1[50],s2[50];
    printf("Введите две строки\n");
    gets(s1);
    gets(s2);
    for(int j = strlen(s2)-1; j>=0; j--){
        if (strchr(s1,s2[j]) != ""){
        k2++;
        }
    }
    printf("Длина отрезка содерж общ символы:%d",k2);

    return 0;
}