#ifndef PROGA_LAB3_H
#define PROGA_LAB3_H

#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include <windows.h>


class triangle{
private:
    double x1,y1,x2,y2,x3,y3;
    [[nodiscard]] double sq() const;
public:
    triangle(double,double,double,double,double,double);
    void move(const std::vector<double>&);

    bool operator ==(const triangle&);
    bool operator !=(const triangle&);
    bool operator >(const triangle&);
    bool operator <(const triangle&);

    void show();
};


class Stack{
private:
    std::stack<int> s;
public:
    Stack() = default;

    void operator<<(const int&);
    void operator>>(const int&);

    void out();
};


#endif //PROGA_LAB3_H
