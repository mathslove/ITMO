//
// Created by mmas6 on 05.06.2020.
//

#ifndef PROGA_GLCUBE_H
#define PROGA_GLCUBE_H
#include "cube_base.h"
#include <glut.h>

struct Glcubie : public cubie {
    int color[6];
    float size;
    Glcubie();
    void setColor(position, int) override ;

    // поворот на плоскости X0Y
    void rotateZ() override;

    // поворот на плоскости X0Z
    void rotateY() override ;

    // поворот на плоскости Y0Z
    void rotateX() override ;

    // рисовка
    void setColor(position);

    void drawCubie(GLenum type);

    void drawCubie(double x, double y, double z);

};


class GlCube : public  Cube {
private:
    float size;
    std::vector<std::vector<std::vector<Glcubie>>> cube;
    bool solved, correct;


    //  Helper storage
    std::vector<std::vector<Glcubie>> slice;
    std::vector<std::vector<int>> f_format;

    //  Drawing storage
    bool ok[4][4][4];
    std::vector<int> rotate;

public:
    int clock;
    int current;
    int i = 0;
//  Constructor
    explicit GlCube(float s);

//  File work
    //  Helpers
    void setCube(const std::vector<std::vector<int>>&) override;
    void saveCube() override;

    void fsetCube(std::ifstream&) override;
    void fsaveCube(std::ofstream&) override;

    std::vector<std::vector<int>>& saved();
//  Rotation
    void rotate90(int, int) override;
    void Rotate(int idx, int angle, int);
    void changeDir();
    void rotate_seq(std::ifstream&);
// Drawing
    void drawCube();
    void reset();
};


#endif //PROGA_GLCUBE_H
