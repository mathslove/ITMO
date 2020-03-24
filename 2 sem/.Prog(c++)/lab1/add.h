#ifndef CHECK_ADD_H
#define CHECK_ADD_H

typedef struct {
    float r;
    float x;
    float y;
} circle;

void func1(int*, int*);
void func1(int&, int&);

void func2(float*);
void func2(float&);

void func3(float*, int);
void func3(float&, int);

void func41(int a[3][3]);
void func42(int (&a)[3][3]);

#endif //CHECK_ADD_H
