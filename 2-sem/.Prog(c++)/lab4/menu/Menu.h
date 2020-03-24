//
// Created by mmas6 on 24.03.2020.
//

#ifndef PROGA_MENU_H
#define PROGA_MENU_H

#include "../TASK/Base.h"
#include "../TASK/My_figures.h"
#include <vector>
#include <algorithm>
#include <conio.h>

class Menu {
public:

    Menu(){system("cls");};
    ~Menu() = default;

    void Start();

    void Main();

private:
    std::vector<IFigure*> sys;
    int command;
    double x, y, sumP, sumS, massAll;
    CVector2D centerMass;
};


#endif //PROGA_MENU_H
