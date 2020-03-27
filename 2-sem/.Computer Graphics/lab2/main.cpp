#include "logic.h"

int main(int argc, char* argv[]) {

    if (argc != 9 && argc != 10){
        std::cerr<<"Wrong amount of arguments!\n"
                   "Expected format:\n"
                   "lab2.exe <in_file> <out_file> <brightness> <thickness> <x_0> <y_0> <x_1> <y_1> <gamma(optional)>";
        return 1;
    }

    std::string inPath = argv[1], outPath = argv[2];
    unsigned short brightness = std::stoi(argv[3]);
    float thickness = std::stof(argv[4]);
    float xS = std::stof(argv[5]), yS = std::stof(argv[6]);
    float xF = std::stof(argv[7]), yF = std::stof(argv[8]);
    float gamma;
    if(argc==10)
        gamma = std::stof(argv[9]);

    pnm img;

    try {
        img.read(inPath);
    }
    catch (std::ifstream::failure&){
        std::cerr<<"File read error!";
        return 1;
    }
    catch (std::bad_alloc&){
        std::cerr<<"Memory allocation error!";
        return 1;
    }

    img.DisplayInfo();

    // main program

    try {
        if (argc == 10) img.DrawLine(xS, yS, xF, yF, thickness, brightness, gamma);
        else img.DrawLine(xS, yS, xF, yF, thickness, brightness);
    }
    catch(...){
        // дописать ошибки
    }

    //

    try {
        img.write(outPath);
    }
    catch (std::ofstream::failure&){
        std::cerr<<"File write error!";
        return 1;
    }

    return 0;
}
