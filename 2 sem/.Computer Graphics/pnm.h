#ifndef PNM_PNM_H
#define PNM_PNM_H

#include <iostream>
#include <vector>
#include <fstream>
#include <exception>

struct RGB{
    unsigned char r,g,b;
};

enum Command{
    inversion = 0,
    mirrorVertically,
    mirrorHorizontally,
    rotate90,
    rotate270,
};

enum Image_t{
    PGM = 5,
    PPM,
};

class pnm {
private:
    std::vector<unsigned char> pgm;
    std::vector<RGB> ppm;
    short int version;
    size_t width, height, depth;

    void readPPM(std::ifstream&);
    void readPGM(std::ifstream&);

    void inversePGM();
    void inversePPM();

    void mirror_v_PGM();
    void mirror_v_PPM();

    void mirror_h_PGM();
    void mirror_h_PPM();

    void rotate90_PGM();
    void rotate90_PPM();

    void rotate270_PGM();
    void rotate270_PPM();

    void writePGM(std::ofstream&);
    void writePPM(std::ofstream&);

public:
    pnm() = default;

    void DisplayInfo();

    void read(const std::string&);
    void read(std::ifstream&);

    void cmd(int);

    void write(std::string&);
    void write(std::ofstream&);

};


#endif //PNM_PNM_H
