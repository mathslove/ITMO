//
// Created by mmas6 on 04.06.2020.
//

#include "glcube.h"
#include <iostream>


//--CUBIE--
Glcubie::Glcubie() {
    std::fill(color, color + 6, undef);
}
void Glcubie::setColor(position newPos, int newColor){
    color[newPos] = newColor;
}

// поворот на плоскости X0Y
void Glcubie::rotateZ()
{
    int tmp = color[right];
    color[right] = color[up];
    color[up] = color[left];
    color[left] = color[down];
    color[down] = tmp;
}

// поворот на плоскости X0Z
void Glcubie::rotateY()
{
    int tmp = color[right];
    color[right] = color[front];
    color[front] = color[left];
    color[left] = color[back];
    color[back] = tmp;
}

// поворот на плоскости Y0Z
void Glcubie::rotateX()
{
    int tmp = color[back];
    color[back] = color[up];
    color[up] = color[front];
    color[front] = color[down];
    color[down] = tmp;
}

void Glcubie::setColor(position pos) {

    static const GLfloat colors[7][3] =
            {   { 0.8f, 0.8f, 1.0f }, //(white)
                { 1.0f, 0.3f, 0.3f }, //(red)
                { 0.3f, 0.3f, 1.0f }, //(blue)
                {0.0f, 1.0f, 0.0f }, //(green)
                { 1.0f, 1.0f, 0.0f }, //(yellow)
                { 1.0f, 0.5f, 0.0f }, //(orange)
                { 0.0f, 0.0f, 0.0f },  // frame
            };

    const GLfloat* C = colors[color[pos]];
    glColor3fv(C);

}

void Glcubie::drawCubie(GLenum type = GL_QUADS) {
    glPushMatrix();
    glBegin(type);

    setColor(up);
    glNormal3f(0, 1, 0);
    glVertex3f(size, size, 0);
    glVertex3f(0, size, 0);
    glVertex3f(0, size, size);
    glVertex3f(size, size, size);

    setColor(down);
    glNormal3f(0, -1, 0);
    glVertex3f(size, 0, size);
    glVertex3f(0, 0, size);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);

    setColor(front);
    glNormal3f(0, 0, 1);
    glVertex3f(size, size, size);
    glVertex3f(0, size, size);
    glVertex3f(0, 0, size);
    glVertex3f(size, 0, size);

    setColor(back);
    glNormal3f(0, 0, -1);
    glVertex3f(size, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);
    glVertex3f(size, size, 0);

    setColor(left);
    glNormal3f(-1, 0, 0);
    glVertex3f(0, size, size);
    glVertex3f(0, size, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);

    setColor(right);
    glNormal3f(1, 0, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size, size, size);
    glVertex3f(size, 0, size);
    glVertex3f(size, 0, 0);

    glEnd();
    glPopMatrix();
}

void Glcubie::drawCubie(double x, double y, double z) {
    glPushMatrix();
    glTranslated(x, y, z);
    drawCubie();
    glPopMatrix();
}


//---CUBE---
//PRIVATE
GlCube::GlCube(float s) {
    cube.resize(3);
    for (int i = 0; i<3;i++){
        cube[i].resize(3);
        for (int j = 0; j<3; j++)
            cube[i][j].resize(3);
    }

    rotate.resize(6);
    current = -1;
    correct = solved = false;
    size = s;
    clock = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                cube[i][j][k].size = (size / 3.0) * 0.95;
    setCube(d_state);
}

//HELPERS
void GlCube::setCube(const std::vector<std::vector<int> > &newCube) {
    std::cout<<newCube.size()<<std::endl;
    if (newCube.size()!=6)
        throw std::length_error("Bad length!\n");
    for (int j = 0; j < 6; ++j) {
        if (newCube[j].size() != 9)
            throw std::length_error("Bad length!\n");
    }

#ifndef RESET
#define RESET
    f_format.resize(6);
    for (int j = 0; j < 6; ++j)
        f_format[j].resize(9);
#endif // RESET
    f_format = newCube;


//      FRONT
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cube[0][i][j].color[front] = newCube[front][i*3+j];
        }
    }
//      BACK
    for (int i = 0; i < 3 ; ++i) {
        for (int j = 0; j < 3; ++j) {
            cube[2][2-i][j].color[back] = newCube[back][i*3+j];
        }
    }
//      UP
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cube[2-i][0][j].color[up] = newCube[up][i*3+j];
        }
    }
//      DOWN
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cube[i][2][j].color[down] = newCube[down][i*3+j];
        }
    }
//      LEFT
    for (int i = 0; i <3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cube[2-j][i][0].color[left] = newCube[left][i*3+j];
        }
    }
//      RIGHT
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cube[j][i][2].color[right] = newCube[right][i*3+j];
        }
    }
}

void GlCube::saveCube() {
    f_format.resize(6);
    for (int i = 0; i < 6; ++i)
        f_format[i].resize(9);

//   FRONT
    for (int i = 0; i<3; i++)
        for (int j = 0; j < 3; ++j)
            f_format[front][i*3+j] = cube[0][i][j].color[front];

//  BACK
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            f_format[back][i*3+j] = cube[2][2-i][j].color[back];

//  UP
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            f_format[up][i*3+j] = cube[2-i][0][j].color[up];

//  DOWN
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            f_format[down][i*3+j] = cube[i][2][j].color[down];

//  LEFT
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            f_format[left][i*3+j] = cube[2-j][i][0].color[left];

//  RIGHT
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            f_format[right][i*3+j] = cube[j][i][2].color[right];
}

//PUBLIC
//SET & SAVING CUBE FROM/IN FILE
void GlCube::fsetCube(std::ifstream &fin) {
    std::vector<std::vector<int>> res(6);
    for (int i = 0; i < 6; ++i) {
        res[i].resize(9);
    }
    std::string side;
    for(int i = 0; i<6;i++){
        fin >> side;
        position p;
        if (side=="FRONT"){
            p = front;
        } else if (side=="DOWN"){
            p = down;
        } else if (side=="UP"){
            p = up;
        } else if (side=="BACK"){
            p = back;
        } else if (side=="LEFT"){
            p = left;
        } else if (side=="RIGHT"){
            p = right;
        } else
            throw std::runtime_error("Wrong file format");

        for (int j = 0; j < 9; ++j) {
            fin >> res[p][j];
        }
    }
    setCube(res);
    std::cout<<std::endl;
}

void GlCube::fsaveCube(std::ofstream &fo) {
    saveCube();

    std::vector<std::string> pos = {"FRONT", "BACK", "UP", "DOWN", "LEFT", "RIGHT"};
    for (int i = 0; i < 6; ++i) {
        fo<<pos[i]<<"\n";
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                fo<<f_format[i][j*3+k]<<" ";
            }
            fo<<"\n";
        }
    }
}

std::vector<std::vector<int>>& GlCube::saved(){
    return f_format;
}

void GlCube::rotate90(int pos, int sign) {
    int x,y,z;
    slice.resize(3);
    for (int k = 0; k < 3; ++k) slice[k].resize(3);
    if (sign != 1 && sign != -1 && sign != 2)
        throw std::runtime_error("Rotation error");
    if (sign == -1)
        sign = 3;

    while(sign--){
        if (pos == up || pos == down){
            y = pos==up ? 0 :2;

            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    slice[i][j] = cube[2-j][y][i];

            for (int i = 0; i <3 ; ++i)
                for (int j = 0; j < 3; ++j){
                    slice[i][j].rotateY();
                    cube[i][y][j] = slice[i][j];
                }
        } else if(pos==front || pos == back){
            z = pos==front ? 0 :2;

            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    slice[i][j] = cube[z][2-j][i];

            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j){
                    slice[i][j].rotateZ();
                    cube[z][i][j] = slice[i][j];
                }
        } else if(pos==left || pos==right){
            x = pos==left ? 0 :2;

            for( int i = 0; i<3; ++i)
                for( int j = 0; j<3; ++j)
                    slice[i][j] = cube[i][2-j][x];

            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j){
                    slice[i][j].rotateX();
                    cube[j][i][x] = slice[i][j];
                }
        }
    }
}

void GlCube::Rotate(int idx, int angle, int angle90) {
    // мы пытаемся покрутить грань с номером idx
    // значит нужно проверить что другая грань уже не крутится

    angle*=clock;
    if (current == -1 || current == idx)
    {
        // обновляем поворот
        rotate[idx] += angle;

        if (rotate[idx] % (angle90 == 1?90:180) != 0)
        {
            current = idx;
        }
        else if(angle90==1)
        {

            // если угол стал кратным 90, то поварачиваем на массиве
            if ((rotate[idx] < 0) ^ (current == 2 || current == 3))
                rotate90(idx, 1);
            else
                rotate90(idx, -1);
            rotate[idx] = 0;
            current = -1;
            i++;
        } else{
            rotate90(idx, 2);
            rotate[idx] = 0;
            current = -1;
            i++;
        }
    }
}

void GlCube::changeDir() {
    clock*=(-1);
}



//DRAWING

void GlCube::drawCube() {
    const double K = 0.65;
    // рисуем корпус - это просто куб черного цвета, размер которого равен K*size
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(((1.0 - K) / 2) * size + K * size / 2, ((1.0 - K) / 2) * size + K * size / 2, ((1.0 - K) / 2) * size + K * size / 2);
    glutSolidCube(size * K);
    glPopMatrix();

    memset(ok, true, sizeof(ok));
    if (current != -1)
    {
        glPushMatrix();
        int i, j, k;

        if (current == front || current == back)
        {
            // 0 <= current <= 1 показывает, что сейчас крутится грань на плоскости X0Y
            // current = 0 - нижняя часть
            // current = 1 - верхняя часть
            k = current == front? 0: 2;
            // следовательно ok слоя  k  устанавливаем в false
            for(i = 0; i < 3; i++)
                for(j = 0; j < 3; j++)
                    ok[k][i][j] = false;

            // теперь нужно покрутить грань под номером current на угол rotate[current]
            // относительно центра этой грани
            // для этого сдвинемся к центру, покрутим, сдвинемся обратно
            glTranslated(size / 2, size / 2, 0);   // сдвигаемся к центру
            glRotatef(rotate[current], 0, 0, 1);   // крутим
            glTranslated(-size / 2, -size / 2, 0); // сдвигаемся обратно
            // рисуем
            for(i = 0; i < 3; i++)
                for(j = 0; j < 3; j++)
                    cube[k][i][j].drawCubie(size / 3 * j, size / 3 * (2-i), size / 3 * (2-k));
        }
            // аналагично с остальными четырмя гранями
        else if (current == up || current == down)
        {
            j = current == up? 0: 2;

            for(i = 0; i < 3; i++)
                for(k = 0; k < 3; k++)
                    ok[k][j][i] = false;

            glTranslated(size / 2, 0, size / 2);
            glRotatef(rotate[current], 0, 1, 0);
            glTranslated(-size / 2, 0, -size / 2);
            for(i = 0; i < 3; i++)
                for(k = 0; k < 3; k++)
                    cube[k][j][i].drawCubie(size / 3 * i, size / 3 * (2-j), size / 3 * (2-k));
        }
        else if (current == left || current == right)
        {
            i = current == left? 0: 2;
            for(j = 0; j < 3; j++)
                for(k = 0; k < 3; k++)
                    ok[k][j][i] = false;

            glTranslated(0, size / 2, size / 2);
            glRotatef(rotate[current], 1, 0, 0);
            glTranslated(0, -size / 2, -size / 2);
            for(j = 0; j < 3; j++)
                for(k = 0; k < 3; k++)
                    cube[k][j][i].drawCubie(size / 3 * i, size / 3 * (2-j), size / 3 * (2-k));
        }
        glPopMatrix();
    }

    for (int i = 0; i<3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                if (ok[i][j][k])
                    cube[i][j][k].drawCubie(size / 3. * k, size / 3. * (2-j), size / 3. * (2-i));
}

void GlCube::reset() {
    setCube(f_format);
}
