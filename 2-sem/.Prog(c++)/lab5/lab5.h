//
// Created by mmas6 on 25.03.2020.
//

#ifndef PROGA_LAB5_H
#define PROGA_LAB5_H

#include <exception>
#include <iostream>
#include "lab5_exceptions.h"

//Задание 1
template <typename T>
void my_swap ( T&, T&);

//Здание 2


template <int N, typename T>
class Queue{
private:
        T queue[N];
        size_t frnt = 0, rear = 0 ;
public:

    void push(T);

    void pop();

    };

#include "lab5.tpp"

#endif //PROGA_LAB5_H
