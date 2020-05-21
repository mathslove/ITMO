//
// Created by mmas6 on 16.05.2020.
//

#ifndef LAB4_PICTURE_H
#define LAB4_PICTURE_H

#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#define Size width * height

enum ColorSpace{
    RGB,
    HSL,
    HSV,
    YCbCr601,
    YCbCr709,
    YCoCg,
    CMY
};

enum ImgFormat{
    PGM = 5,
    PPM
};

struct Pixel {
    unsigned char a;
    unsigned char b;
    unsigned char c;
};

class picture {
private:
    std::vector<Pixel> ppm;
    short version;
    size_t width, height, depth;
    ColorSpace imgCS;

//  picture.cpp
    void open_single(const std::string&);
    void open_triple(const std::string&);

    void save_single(const std::string&);
    void save_triple(const std::string&);

//  logic.cpp
    void toRgb();
public:
    picture():
    ppm(0),version(0),width(0), height(0), depth(0), imgCS(RGB){};
    ~picture(){
        ppm.clear();
        ppm.~vector<Pixel>();
    };

//  picture.cpp
    void setCS(ColorSpace);
    void open(const std::string&, int);
    void save(const std::string&, int);

//  logic.cpp
    void solve(ColorSpace);

};


#endif //LAB4_PICTURE_H
