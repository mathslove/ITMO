//
// Created by mmas6 on 24.03.2020.
//

#include "My_figures.h"

Circle::Circle() {
    this->initFromDialog();
}


void Circle::initFromDialog() {
    std::cout << "\tAdd circle center coords in format: x y\n\t";
    std::cin >> _c.x >> _c.y;
    std::cout << "\tAdd circle radius:\n\t";
    std::cin >> _r;
    std::cout << "\tAdd weight:\n\t";
    std::cin >> _weight;
}

double Circle::square() {
    return M_PI*pow(_r,2);
}

double Circle::perimeter() {
    return 2.0*M_PI*_r;
}

double Circle::mass() const {
    return _weight;
}

CVector2D Circle::position() {
    return _c;
}

bool Circle::operator==(const IPhysObject & object) const
{
    return mass() == object.mass();
}

bool Circle::operator<(const IPhysObject & object) const
{
    return mass() < object.mass();
}

void Circle::draw() {
    std::cout<<"Circle radius = "<<_r<<std::endl;
    std::cout<<"Circle center in "<<_c.x<<" "<<_c.y<<std::endl;
    std::cout<<"Mass: "<<_weight<<std::endl<<std::endl;
}

const char* Circle::classname()
{
    return _name;
}
unsigned Circle::size()
{
    return sizeof(*this);
}