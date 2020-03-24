//
// Created by mmas6 on 23.03.2020.
//

#include "My_figures.h"

double dist(CVector2D& a, CVector2D& b){
    return sqrt(pow((b.x-a.x),2)+pow((b.y-a.y),2));
}

Triangle::Triangle() {
    this->initFromDialog();
}

void Triangle::initFromDialog() {
    std::cout << "\tAdd the first coords in format: x y\n\t";
    std::cin >> _a.x >> _a.y;
    std::cout << "\tAdd the second coords in format: x y\n\t";
    std::cin >> _b.x >> _b.y;
    std::cout << "\tAdd the third coords in format: x y\n\t";
    std::cin >> _c.x >> _c.y;
    std::cout << "\tAdd weight:\n\t";
    std::cin >> _weight;
}

double Triangle::square() {
    double res = fabs(0.5*((_a.x-_c.x)*(_b.y-_c.y)-(_a.y-_c.y)*(_b.x-_c.x)));
    return res;
}

double Triangle::perimeter() {
    return dist(_a,_b) + dist(_b,_c) + dist(_a,_c);
}

double Triangle::mass() const {
    return _weight;
}

CVector2D Triangle::position() {

    CVector2D center;
    center.x = (_a.x + _b.x + _c.x) / 3;
    center.y = (_a.y + _b.y + _c.y) / 3;
    return center;
}

bool Triangle::operator==(const IPhysObject & object) const
{
    return mass() == object.mass();
}

bool Triangle::operator<(const IPhysObject & object) const
{
    return mass() < object.mass();
}

void Triangle::draw() {
    std::cout << "Name: " << _name << std::endl;
    std::cout << "Position: " << position().x <<" "<< position().y << std::endl;
    std::cout << "Weight: " << _weight << std::endl;
    std::cout << "Size: " << size() << std::endl;
    std::cout << std::endl<<std::endl;
}

const char* Triangle::classname()
{
    return _name;
}
unsigned Triangle::size()
{
    return sizeof(*this);
}