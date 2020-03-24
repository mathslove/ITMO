#include "lab3.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);

    triangle abc = triangle(1.5, 2.3, 6.5, 6.9, -1.4, -2);
    triangle def = triangle(10.5, 20.3, 9.7, 9.9, 0, 0);
    std::vector<double > a = {1.2,3.6};

    std::cout<<std::boolalpha<< (abc==def) <<std::endl;
    std::cout<< (abc!=def) <<std::endl;
    std::cout<< (abc>def) <<std::endl;
    std::cout<< (abc<def) <<std::endl;

    abc.show();
    abc.move(a);
    abc.show();

    Stack s = Stack();
    s<<123;
    s<<234;
    s.out();
    s>>0;
    s>>0;
    s>>0;

    return 0;
}