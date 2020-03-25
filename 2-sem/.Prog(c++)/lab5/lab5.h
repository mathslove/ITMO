//
// Created by mmas6 on 25.03.2020.
//

#ifndef PROGA_LAB5_H
#define PROGA_LAB5_H

#include <exception>
#include <stdexcept>
#include <iostream>

//Задание 1
template <typename T>

void my_swap ( T & first , T & second )
{
    T temp(first) ;
    first = second ;
    second = temp ;
}

//Здание 2

//Мой класс исключений
class QueueException: public std::exception {
public:
        virtual const char* what() const noexcept;
    };

template <int N, typename T>

class Queue{
private:
        T queue[N];
        std::size_t frnt = 0, rear = 0 ;
public:

    void push(T val){
        try{
            if ( rear+1 == frnt || ( rear + 1 ==N && !frnt )) {
                throw QueueException();
            }
            rear++;
            if ( rear==N ) rear = 0 ;
            queue [ rear ] = val;
        }
        catch (QueueException& e){
            std::cerr<<e.what()<<std::endl;
        }
        }

    void pop(){
        try{
        if ( frnt == rear ) {
            throw QueueException();
        }
        frnt++;
        if ( frnt==N ) frnt = 0 ;
        }
        catch (QueueException& e){
            std::cerr<<e.what()<<std::endl;
        }
    }

    };



#endif //PROGA_LAB5_H
