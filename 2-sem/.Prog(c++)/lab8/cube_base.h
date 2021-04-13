#pragma once
#include <vector>
#include <stdexcept>
#include <fstream>


enum Color {
    white = 0,
    red = 1,
    blue = 2,
    green = 3,
    yellow = 4,
    orange = 5,
    undef = 6,
};

enum position{
    front,
    back,
    up,
    down,
    left,
    right,
};

std::vector<std::vector<int>> d_state = {
        {0,0,0,0,0,0,0,0,0},
        {4,4,4,4,4,4,4,4,4},
        {1,1,1,1,1,1,1,1,1},
        {5,5,5,5,5,5,5,5,5},
        {3,3,3,3,3,3,3,3,3},
        {2,2,2,2,2,2,2,2,2},
};

// Small cube from Cube
struct cubie {

    virtual void setColor(position, int) = 0;

    // поворот на плоскости X0Y
    virtual void rotateZ() = 0;

    // поворот на плоскости X0Z
    virtual void rotateY() = 0;

    // поворот на плоскости Y0Z
    virtual void rotateX() = 0;
};


// Basic abstract cube
class Cube{
private:

public:
//  Helpers
    virtual void setCube(const std::vector<std::vector<int>>&) = 0;
    virtual void saveCube() = 0;

//  File work
    virtual void fsetCube(std::ifstream&) = 0;
    virtual void fsaveCube(std::ofstream&) = 0;

//  Rotation
    virtual void rotate90(int, int) = 0;
};