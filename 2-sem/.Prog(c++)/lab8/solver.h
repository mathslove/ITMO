//
// Created by mmas6 on 10.06.2020.
//

#ifndef PROGA_SOLVER_H
#define PROGA_SOLVER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include "glcube.h"

typedef std::vector<int> cubestate;


class solver {
public:
    solver()=default;
    solver(std::vector<std::vector<int>>&);
    ~solver() = default;
private:
    std::vector<std::vector<int>> cv;
    std::string ColortoSide(int c);

    void mainSolve(int, std::vector<std::string>);
    cubestate id(cubestate);
    int inverse(int);
    cubestate applyMove(int, cubestate);
};


#endif //PROGA_SOLVER_H
