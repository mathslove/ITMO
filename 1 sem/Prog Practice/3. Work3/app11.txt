#include <windows.h>
#include <stdio.h>
#include "circle.h"

int main(int argc, char *argv[]){
    SetConsoleOutputCP(CP_UTF8);

    int x,y;
    float r;
    printf("Введите координаты центра окружности, затем её радиус\n");
    scanf("%d",&x);
    scanf("%d",&y);
    scanf("%f",&r);
    struct point O;
    O = makepoint(x,y);
    struct circle W;
    W = makecircle(O, r);
    float S = circleS(W);
    float P = circleP(W);
    printf("Площадь круга: %f \n Длина окружности: %f \n",S,P);
    return 0;
}