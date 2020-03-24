//
// Created by mmas6 on 23.03.2020.
//

#ifndef PROGA_MY_FIGURES_H
#define PROGA_MY_FIGURES_H

#include "Base.h"

class Triangle : public IFigure
{
public:
    Triangle();

    ~Triangle() = default;

    void initFromDialog() override;

    double square() override;

    double perimeter() override;

    [[nodiscard]] double mass() const override;

    CVector2D position() override;

    bool operator== ( const IPhysObject& ob ) const override;

    bool operator< ( const IPhysObject& ob ) const override;

    void draw() override;

    const char* classname() override;

    unsigned int size() override;

private:
    CVector2D _a,_b,_c;
    double _weight = 0;
    const char* _name = "Triangle";
};

class Circle : public IFigure
{
public:
    Circle();

    ~Circle() = default;

    void initFromDialog() override;

    double square() override;

    double perimeter() override;

    [[nodiscard]] double mass() const override;

    CVector2D position() override;

    bool operator== ( const IPhysObject& ob ) const override;

    bool operator< ( const IPhysObject& ob ) const override;

    void draw() override;

    const char* classname() override;

    unsigned int size() override;

private:
    CVector2D _c;
    double _r = 0;
    double _weight = 0;
    const char* _name = "Circle";
};

#endif //PROGA_MY_FIGURES_H
