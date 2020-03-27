#ifndef LAB2_LOGIC_H
#define LAB2_LOGIC_H

#include <iostream>
#include <vector>
#include <fstream>
#include <exception>
#include <cmath>
#include <algorithm>
#include <utility>


enum Image_t{
    PGM = 5
};

class pnm{
private:
    std::vector<std::vector<unsigned char>> pgm;
    short version;
    size_t width, height, depth;

    void read(std::ifstream&);

    void write(std::ofstream&);

    void plot(bool, int,int, double, float, float);

    int ipart(double);

    int round(double);

public:

    void read(const std::string&);

    void DisplayInfo();

    void DrawLine(float&, float&, float&,
                  float&, float&, unsigned short&, float = 0);

    void write(const std::string&);

};

#endif
