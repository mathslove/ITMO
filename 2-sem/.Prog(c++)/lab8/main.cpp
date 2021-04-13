/**
 Выполнил: Маслов Михаил M3106
 Лабораторная работа №8. Кубик Рубика.

 Спроектировать и реализовать программу, имитирующую сборку ​Кубика Рубика​ 3x3.
 К программе предъявляются следующие функциональные требования:
 - Сохранение и чтение состояния кубика рубика из файла;
 - Проверка корректности текущего состояния (инвариант состояний кубика);
 - Вывод в консоль текущего состояния;
 - Вращение граней кубика рубика с помощью вводимых команд;
 - Генерация случайного состояния Кубика Рубика, корректного с точки зрения инварианта состояний;
 - Нахождения “решения” для текущего состояния в виде последовательности поворотов граней.

 Нефункциональные требования:
 - Программа должны быть спроектирована с использованием ООП;
 - Логические сущности должны быть выделены в отдельные классы.

 Критерии оценки:
 - Логично выстроенная архитектура приложения;
 - Применение возможностей языка программирования С++, включая стандартную библиотеку.

 Дополнительно (за дополнительные баллы):
 - Реализовать графический интерфейс приложения, с использованием OpenGL Utility Toolkit.
 */

#include <iostream>
#include "glcube.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

#define CUBE_SIZE 13
#define TIMER 3
// координаты источника света
GLfloat lightPos[] = { 0, 100, 200, 0 };
// проекции угла поворота на оси
int xRot = 24, yRot = -34, zRot = 0;
// отдаление
double translateZ = -35.0;
// кубик-рубик
GlCube cube(CUBE_SIZE);
// флаг того, крутится куб сам, или нет (будет переключаться правой кнопкой мыши)
int timerOn = 0;
bool solveB = false;
std::vector<std::pair<int,int>> seq(0);
std::string fi,fo;

void display()
{
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glTranslatef(0, 0, translateZ);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
    cube.drawCube();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fAspect = (GLfloat)w / (GLfloat)h;
    gluPerspective(60, fAspect, 1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    glClearColor(0.1, 0.7, 0.6, 1.5);
    // инициализируем случайные числа
    srand(time(0));

    // освещение
    float mat_specular[] = { 0.3, 0.3, 0.3, 0 };
    float diffuseLight[] = { 0.2, 0.2, 0.2, 1 };
    float ambientLight[] = { 0.9, 0.9, 0.9, 1.0 };
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void specialKeys(int key, int, int)
{
    // клавиши влево/вправо вращают по Y
    // клавиши вверх/вниз вращают по X
    // F1 - возвращает в начальное положение
    if (key == GLUT_KEY_DOWN)
    {
        xRot += 3;
        if (xRot >= 360)
            xRot -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_UP)
    {
        xRot -= 3;
        if (xRot < 0)
            xRot += 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_RIGHT)
    {
        yRot += 3;
        if (yRot >= 360)
            yRot -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_LEFT)
    {
        yRot -= 3;
        if (yRot < 0)
            yRot += 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_HOME)
    {
        translateZ += 5;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_END)
    {
        translateZ -= 5;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_F1)
    {
        cube.reset();
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_F2)
    {
        solveB = 1-solveB;
        /*cube.saveCube();
        solver a(cube.saved());
        std::ifstream storage("storage.txt");*/

        /*while(!storage.eof()) {
            unsigned char rot = storage.get();
            unsigned char tmp = storage.get();
            int qty = tmp-'0';
            int qty0 = rot-'0';
            seq.emplace_back(qty0,qty);
            *//*if (rot == 'F') {
                cube.clock=-1;
                for (int i = 0; i < qty; i++) {
                    cube.Rotate(front, 3);
                    display();
                }
                cube.clock=1;
            } else if (rot == 'B') {
                for (int i = 0; i < qty; i++) {
                    cube.Rotate(back, 3);
                    display();
                }
            }*//*
        }*/
        std::reverse(seq.begin(), seq.end());
        cube.clock=-1;
        cube.i = 0;
        cube.Rotate(seq[cube.i].first, 3, seq[cube.i].second);
        glutPostRedisplay();
    }
}

void keys(unsigned char key, int, int)
{
    // если нажали клавишу от 0 до 5 - начинаем поворот на 3 градуса
    if (cube.current == -1 && key >= '0' && key < '6')
    {
        cube.Rotate(key - '0', 3,1);
        display();
    }else if( key == 'z'){
        cube.changeDir();
    }else if( key == 'f'){
        std::ifstream in(fi);
        cube.fsetCube(in);
        in.close();
    }else if( key == 's'){
        std::ofstream out(fo);
        cube.fsaveCube(out);
        out.close();
    }else if( key == 'c'){
        std::ofstream console;
        console.basic_ios<char>::rdbuf(std::cout.rdbuf());
        cube.fsaveCube(console);
        console.close();
    }
}

void mouse(int key, int state, int, int)
{
    if (key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // переключаем флаг
        timerOn = 1 - timerOn;
    }
}

void timer(int)
{
    glutTimerFunc(TIMER, timer, 0);
    if (timerOn)
    {
        // если включен автоматический поворот, и смотрим
        // если сейчас никакая грань не крутится, то начинаем крутить случайную,
        // иначе крутим текущую
        if (cube.current == -1) {
            int tmp = rand() % 6;
            seq.push_back({tmp,1});
            keys(tmp + '0', 0, 0);
        }
        else
            cube.Rotate(cube.current, 3,1);
    }
    else
    {
        if(!seq.empty() && cube.i <seq.size()){
            cube.Rotate(seq[cube.i].first, 3,seq[cube.i].second);
        }else if (cube.current != -1)
            cube.Rotate(cube.current, 3,1);
    }
    display();
}

int main(int argc, char** argv)
{
    for (int i = 1; i < argc && i < 6; i+=2) {
        if (argc-i>=1 && strcmp(argv[i], "-i") == 0) {
            fi = argv[i+1];
        }
        if (argc-i>=1 && strcmp(argv[i], "-o") == 0) {
            fo = argv[i+1];
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(1, 1);
    glutCreateWindow("Cube");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutMouseFunc(mouse);
    glutTimerFunc(TIMER, timer, 0);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}