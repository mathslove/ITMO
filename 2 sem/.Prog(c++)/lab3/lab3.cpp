#include "lab3.h"

triangle::triangle(double x1,double y1,double x2,double y2,double x3,double y3){
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->x3 = x3;
    this->y3 = y3;
}

double triangle::sq() const {
    double res = fabs(0.5*((x1-x3)*(y2-y3)-(y1-y3)*(x2-x3)));
    return res;
}

void triangle::move(const std::vector<double >& vec){
    x1 += vec[0];
    y1 += vec[1];
    x2 += vec[0];
    y2 += vec[1];
    x3 += vec[0];
    y3 += vec[1];
}

bool triangle::operator==(const triangle& a) {
    return sq() == a.sq();
}
bool triangle::operator!=(const triangle& a) {
    return sq() != a.sq();
}
bool triangle::operator>(const triangle& a) {
    return sq() > a.sq();
}
bool triangle::operator<(const triangle& a) {
    return sq() < a.sq();
}

void triangle::show() {
    std::cout<<"Координаты фигруы"<<std::endl;
    std::cout<<x1<<" "<<y1<<std::endl;
    std::cout<<x2<<" "<<y2<<std::endl;
    std::cout<<x3<<" "<<y3<<std::endl;
    std::cout<<"¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯"<<std::endl;
}

void Stack::operator<<(const int & x) {
    if (s.size()>=100) std::cout<<"Стек полон!"<<std::endl;
    else
        s.push(x);
}

void Stack::operator>>(const int&) {
    if (s.empty()) std::cout<<"Стек пуст!"<<std::endl;
    else
        s.pop();
}

void Stack::out(){
    std::vector<int> t(s.size());
    size_t size = s.size();
    for (size_t i = 0; i < size; i++){
        std::cout<<s.top()<<" ";
        t.push_back(s.top());
        s.pop();
    }
    for (size_t i = 0; i<size; i++){
        s.push(t[t.size()-1]);
        t.pop_back();
    }
    std::cout<<std::endl;
}

