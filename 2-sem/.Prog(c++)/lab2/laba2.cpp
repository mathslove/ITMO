#include "laba21.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);
//    my_vector_menu();

    my_vector a = my_vector();

    const my_vector b = my_vector(a);

    my_vector c = my_vector(1.3,2.15,3.5);

    std::vector<double> vec = {1.5,2.3,1.44444};
    my_vector d = my_vector(vec);


    d.sum(c);
    d.out();

    d.sub(c);
    d.out();

    std::cout<<d.len()<<std::endl;

    d.angle(c);

    c.out();
    return 0;
}