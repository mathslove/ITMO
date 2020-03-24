#ifndef PROGA_LABA21_H
#define PROGA_LABA21_H

#include <vector>
#include <iostream>
#include <cmath>
#include <windows.h>

class my_vector {
private:
    double x,y,z;
public:
    my_vector();
    my_vector(const my_vector&);
    my_vector(double, double, double);
    my_vector(const std::vector<double>&);

    my_vector sum(my_vector&);
    my_vector sub(my_vector&);
    double len();
    double angle(my_vector&);
    void out();
};
//
//class my_vector_menu {
//private:
//    int flag = 0;
//    my_vector vec;
//
//    void default_menu() {
//        ;
//    }
//    void custom_menu() {
//        ;
//    }
//public:
//    my_vector_menu() {
//        std::cout << "\t\tHello, my name is \n";
//        std::cout << "\tThis is vector program\n";
//        int in;
//        default_menu();
//        do {
//            std::cin >> in;
//            if () {
//                custom_menu();
//            }
//        } while(in != 0);
//    }
//};

#endif //PROGA_LABA21_H
