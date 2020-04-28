#include <iostream>
#include <vector>
#include <set>
#include "lab6.h"

bool foo(int x) {
    return x < 0;
}
bool comp(int x, int y) {
    return x < y;
}

int main(){

    std::vector<int> A = {1, 5, 3};
    std::set<double> B = {-1, 2, 3.};
    MyArray C;
    C.push_back(1);
    C.push_back(2);
    C.push_back(3);

    std::cout << std::boolalpha << noneOf(A.begin(), A.end(), foo) << " : " << noneOf(B.begin(), B.end(), foo) << std::endl;
    std::cout << isSorted(A.begin(), A.end(), comp) << " : " << isSorted(B.begin(), B.end(), comp);
    std::cout<<" : "<< isSorted(C.begin(), C.end(), comp) << std::endl;
    std::cout << findNot(A.begin(), A.end(), 1) << " : " << findNot(B.begin(), B.end(), 1) << std::endl;

    return 0;
}