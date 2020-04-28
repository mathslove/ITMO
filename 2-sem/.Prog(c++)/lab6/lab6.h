//
// Created by mmas6 on 15.04.2020.
//

#ifndef PROGA_LAB6_H
#define PROGA_LAB6_H

class MyArray {
public:
    auto begin() { return _vec.begin(); }
    auto end() { return _vec.end(); }
    auto push_back(int a){ _vec.push_back(a);}
private:
    std::vector<int> _vec;
};

template <typename containerIterator, typename object>
bool noneOf(containerIterator, containerIterator, bool (&f)(object));
template <typename containerIterator, typename object>
bool isSorted(containerIterator, containerIterator, bool (&f)(object, object));
template <typename containerIterator, typename object>
object findNot(containerIterator, containerIterator, object);

#include "lab6_tpp.h"

#endif //PROGA_LAB6_H
