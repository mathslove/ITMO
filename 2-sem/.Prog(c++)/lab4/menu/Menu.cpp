//
// Created by mmas6 on 24.03.2020.
//

#include "Menu.h"

enum Commands
{
    ADD = 1,
    SHOW_ALL,
    SUM_PERIMETERS,
    SUM_AREAS,
    CENTRE_MASS,
    MEMORY,
    SORT,
    EXIT=0
};

enum Figure
{
    CIRCLE = 1,
    TRIANGLE
};

void Menu::Start() {
    std::cout<<"\n\tHI!\n"
               "\tWELCOME TO MY PROGRAM!\n\n"
               "\tI'll show you what I can, just choose the command:\n"
               "\t\t1. Add figure\n"
               "\t\t2. Show all figures\n"
               "\t\t3. Sum all perimeters\n"
               "\t\t4. Sum all areas\n"
               "\t\t5. System weight center\n"
               "\t\t6. Show figures memory\n"
               "\t\t7. Sort\n"
               "\t\t0. Exit\n\n"
               "\tCommand is gonna be: ";
    std::cin>>command;
    Main();

}

void Menu::Main() {
    int cmd;
    system("cls");
    if((command >1 and command < 8) and sys.empty()){
        std::cout<<"System is empty!\n";
        getch();
        system("cls");
        Start();
        }else{
        switch (command) {
            case ADD:{
                std::cout << "\t1. Circle" << std::endl;
                std::cout << "\t2. Triangle" << std::endl;
                std::cout << "\tAdd command: ";
                std::cin >> cmd;
                std::cout << std::endl;
                switch (cmd)
                {
                    case CIRCLE:
                        sys.push_back(new Circle());
                        break;
                    case TRIANGLE:
                        sys.push_back(new Triangle());
                        break;
                    default:
                        std::cout << "\tFigure not found" << std::endl;
                        break;
                }
                break;
            }
            case SHOW_ALL:{
                for (auto& figure : sys)
                    figure->draw();
                break;
            }
            case SUM_PERIMETERS:{

                sumP = 0;
                for (auto& figure : sys)
                    sumP += figure->perimeter();
                std::cout << "System perimeter: " << sumP << std::endl;
                std::cout << std::endl;
                break;
            }
            case SUM_AREAS:{
                sumS = 0;
                for (auto& figure : sys)
                    sumS += figure->square();
                std::cout <<"Steam area: " << sumS << std::endl;
                std::cout <<std::endl;
                break;
            }
            case CENTRE_MASS:{
                massAll = 0;
                x = 0;
                y = 0;
                for (auto& figure : sys) {
                    x += figure->position().x * figure->mass();
                    y += figure->position().y * figure->mass();
                    massAll += figure->mass();
                }
                centerMass.x = x / massAll;
                centerMass.y = y / massAll;
                std::cout << "Center weight coords: " << centerMass.x <<" "<< centerMass.y << std::endl;
                std::cout << std::endl;
                break;
            }
            case MEMORY:{
                std::cout << "Figures memory: ";
                for (auto& figure : sys)
                    std::cout << figure->size() << " ";
                std::cout << std::endl;
                std::cout << std::endl;
                break;
            }
            case SORT:{
                std::sort(sys.begin(), sys.end(), [](IFigure* x, IFigure* y) {return *x < *y; });
                std::cout << "Successes" << std::endl;
                std::cout << "Figures weight: ";
                for (auto& figure : sys)
                    std::cout << figure->mass() << " ";
                std::cout << std::endl;
                std::cout << std::endl;
                break;
            }
            case EXIT:{
                system("cls");
                exit(0);
            }
            default:
                std::cout << "Command not found" << std::endl;
                std::cout << std::endl;
                break;
        }
    }
    getch();
    system("cls");
    Start();
}