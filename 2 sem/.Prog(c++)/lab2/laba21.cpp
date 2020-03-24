#include "laba21.h"

my_vector::my_vector() {
    x = 0;
    y = 0;
    z = 0;
}

my_vector::my_vector(const my_vector &v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

my_vector::my_vector(double x, double y, double z) {
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

my_vector::my_vector(const std::vector<double>& c) {
    x = c[0];
    y = c[1];
    z = c[2];
}

my_vector my_vector::sum(my_vector& b){
    my_vector res(x+b.x,y+b.y,z+b.z);
    return  res;
}

my_vector my_vector::sub(my_vector& b){
    my_vector res(x-b.x,y-b.y,z-b.z);
    return  res;
}

double my_vector::len() {
    double res = sqrt(pow(this->x,2)+pow(this->y,2)+pow(this->z,z));
    return res;
}

double my_vector::angle(my_vector& b){
    double res = acos((x*b.x+y*b.y+z*b.z)/(len()*b.len()));
    return res;
}

void my_vector::out() {
    std::cout<<"Координата вектора: "<<this->x<<this->y<<this->z<<std::endl;
    std::cout<<"Длина вектора: "<<len()<<"\n\n";
}