/*
* Лабораторная работа по программированию #5
* Выполнил:	Маслов Михаил
* Группа:	M3106
* Вариант:	3
*
* Задание:
	Написать шаблонную функцию или класс согласно варианту. Описать класс-исключение или
    иерархию классов-исключений. Генерировать исключения в соответствующих исключительных
    ситуациях. Если у вас есть другие предложения по исключительным ситуациям – используйте их.
* Вариант:
 	|______________________________________Функкия___________________________________|
 	|_________________Описание__________________________|_______Параметр шаблона_____|
 	|Меняет значения двух переменных одного типа местами|       Тип переменных.      |
    |(swap)_____________________________________________|____________________________|

    |_____________________________________Классы_____________________________________|
    |_______Описание_______|_____Параметры шаблона_____|________Исключения___________|
    |   Очередь из макс. N |       int N, class T      |Переполнение очереди. Изъятие|
    |   элементов типа T   |                           |элемента из пустой очереди.  |
 */

#include <iostream>
#include "lab5.h"

int main(){

    int a = 5, b = 6;
    std::cout<<"a = "<<a<<" b = "<<b<<std::endl;
    my_swap(a,b);
    std::cout<<"a = "<<a<<" b = "<<b<<std::endl;



    Queue<3, int> q;

    q.pop();

    q.push(1);
    q.push(2);
    q.push(3);

    q.push(4);
    return 0;
}