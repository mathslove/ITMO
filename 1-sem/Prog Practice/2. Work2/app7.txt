#include <windows.h>

#include <stdio.h>
#include <math.h>

// К заданию 1
enum org_name{  
    ZAO,
    OOO,
    IP,
};

// К заданию 2
struct trinagle {  
    float x1,y1,x2,y2,x3,y3,x4,y4;
};

// К задание 3
union cond{
    struct{
        unsigned int on_off : 1;
        unsigned int SDcard : 1;
        unsigned int CompactFlash : 1;
        unsigned int MemoryStick : 1;
    }bitfield;
    int x16;
};

int main(){
    SetConsoleOutputCP(CP_UTF8);  // Изменение пкодировки на UTF8 для локализации русского(CLion, GCC)

    //Задание 1
    enum org_name x;
    x = OOO;
    printf("Значение целого числа для OOO: %d\n\n", x);

    // Задание 2
    float a,s;
    struct trinagle ABC;
    ABC.x1 = 1;
    ABC.y1 = -1;
    ABC.x2 = 3;
    ABC.y2 = -1;
    ABC.x3 = 3;
    ABC.y3 = 3;
    ABC.x4 = 1;
    ABC.y4 = 3;
    a = sqrtf(pow((ABC.x2 - ABC.x1), 2) + pow((ABC.y2 - ABC.y1), 2));
    s = pow(a,2);
    printf("Площадь квадрата равна: %f\n\n", s);
    // Задание 3
    union cond y;
    printf("Введите 16-ричное число:");
    scanf("%x\n", &y);
    printf(" Card Reader: %d\n SD card: %d\n Compact Flash: %d\n Memory Stick: %d\n", y.bitfield.on_off,y.bitfield.SDcard,y.bitfield.CompactFlash,y.bitfield.MemoryStick);

    return 0;
}