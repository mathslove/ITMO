/*

 Реализовать ​ кольцевой буфер в виде stl-совместимого
 контейнера (например, может быть использован с стандартными алгоритмами),
 обеспеченного итератором произвольного доступа.
 Реализация не должна использовать ни одни из контейнеров  STL.

 Буфер должен обладать следующими возможностями:
 1. Вставка и удаление в конец
 2. Вставка и удаление в начало
 3. Вставка и удаление в произвольное место по итератору
 4. Доступ в конец, начало
 5. Доступ по индексу
 6. Изменение капасити

 Выполнил: M3106 Маслов Михаил

 */

#include <iostream>
#include "circular_buffer.h"
#include <algorithm>
//#include "boost/circular_buffer.hpp"

void print(circular_buffer<int>& cb){
    for (int i : cb){
        std::cout<<i<<" ";
    }
    std::cout<<"\n\n";
}

void print(const char* s){
    std::cout<<s<<std::endl;
}

int main(){

    circular_buffer<int> b;

    print("set_capacity 5");
    b.set_capacity(5);
    print("");

    print("insert begin 10");
    b.insert(b.begin(), 10);
    print(b);

    print("push_back 11");
    b.push_back(11);
    print(b);

    print("push_front 12");
    b.push_front(12);
    print(b);

    print("erase begin");
    b.erase(b.begin());
    print(b);

    print("push_front 1");
    b.push_front(1);
    print(b);

    print("push_back 2");
    b.push_back(2);
    print(b);

    print("std::sort");
    std::sort(b.begin(), b.end());
    print(b);

    print("std::reverse");
    std::reverse(b.begin(), b.end());
    print(b);

    print("pop_back");
    b.pop_back();
    print(b);

    print("pop_front");
    b.pop_front();
    print(b);

    print("capacity");
    std::cout<<b.capacity()<<"\n";
    print("size");
    std::cout<<b.size()<<"\n";

    return 0;
}