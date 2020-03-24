#include <iostream>
#include "add.h"

int main()
{
    int a = 5, b = 4;
    func1(&a, &b);
    std::cout << a <<' '<< b << std::endl;

    int x = 2, y = 3;
    func1(x, y);
    std::cout << x <<' '<< y << std::endl;
    std::cout << std::endl;
//----------------------
    float z = 2.8;
    func2(&z);
    std::cout << z << std::endl;

    z = 2.8;
    func2(z);
    std::cout << z << std::endl;
    std::cout << std::endl;
//----------------------
    circle c;
    c.r = 10;
    func3(&c.r, 3);
    std::cout << c.r << std::endl;

    c.r = 10;
    func3(c.r, 3);
    std::cout << c.r << std::endl;
    std::cout << std::endl;
//----------------------
    int mas[3][3] = {{1,2,3},{4,5,6},{7,8,9}} ;
    func41(mas);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            std::cout << mas[i][j] << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;

    func42(mas);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            std::cout << mas[i][j] << " ";
        std::cout << std::endl;
    }
    return 0;
}