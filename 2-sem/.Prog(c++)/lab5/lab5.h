//
// Created by mmas6 on 25.03.2020.
//

#ifndef PROGA_LAB5_H
#define PROGA_LAB5_H

#include <list>
#include <iostream>
#include "lab5_exceptions.h"

//Задание 1
template <typename T>
void my_swap ( T&, T&);


//Здание 2
template <int N, typename T>
class Queue
{
public:

    void push(const T&);
    T pop();

private:
    std::list<T> myList;
    unsigned size = N;
};

#include "lab5_1.h"


#endif //PROGA_LAB5_H
