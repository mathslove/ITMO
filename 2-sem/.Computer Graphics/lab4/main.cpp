#include <iostream>
#include "picture.h"

int main(int argc, char* argv[]){

    ColorSpace CS, Conv;
    int ic, oc;
    std::string InPath, OutPath;

    try{
        if (argc != 11)
            throw std::invalid_argument("Must be 11 arguments!\n"
                                        "Expected format:\n"
                                        "lab4.exe -f <from_color_space> -t <to_color_space> -i <count> <input_file_name> -o <count> <output_file_name>\n");
    }
    catch (std::invalid_argument& e) {
        std::cerr<<e.what();
        return 1;
    }

    for (int pos = 0; pos<argc; pos++){
        std::string buf = argv[pos];

        if (buf == "-f"){
            pos++;
            buf = argv[pos];
            if (buf == "RGB")
            {
                CS = RGB;
                continue;
            }
            if (buf == "HSL")
            {
                CS = HSL;
                continue;
            }
            if (buf == "HSV")
            {
                CS = HSV;
                continue;
            }
            if (buf == "YCbCr.601")
            {
                CS = YCbCr601;
                continue;
            }
            if (buf == "YCbCr.709")
            {
                CS = YCbCr709;
                continue;
            }
            if (buf == "YCoCg")
            {
                CS = YCoCg;
                continue;
            }
            if (buf == "CMY")
            {
                CS = CMY;
                continue;
            }
            std::cerr<<"Unknown color space \""<< buf << "\". Terminating";
            return 1;
        }

        if (buf == "-t"){
            pos++;
            buf = argv[pos];
            if (buf == "RGB")
            {
                Conv = RGB;
                continue;
            }
            if (buf =="HSL")
            {
                Conv = HSL;
                continue;
            }
            if (buf == "HSV")
            {
                Conv = HSV;
                continue;
            }
            if (buf == "YCbCr.601")
            {
                Conv = YCbCr601;
                continue;
            }
            if (buf == "YCbCr.709")
            {
                Conv = YCbCr709;
                continue;
            }
            if (buf == "YCoCg")
            {
                Conv = YCoCg;
                continue;
            }
            if (buf == "CMY")
            {
                Conv = CMY;
                continue;
            }
            std::cerr<<"Unknown color space \""<< buf << "\". Terminating";
            return 1;
        }

        if(buf == "-i"){
            pos++;
            buf = argv[pos];
            if(buf == "1")
                ic = 1;
            else if (buf == "3")
                ic = 3;
            else {
                std::cerr << "Only 1 or 3 input files!\n";
                return 1;
            }
            pos++;
            buf = argv[pos];
            InPath = buf;
            continue;
        }

        if (buf == "-o"){
            pos++;
            buf = argv[pos];
            if(buf == "1")
                oc = 1;
            else if (buf == "3")
                oc = 3;
            else {
                std::cerr << "Only 1 or 3 output files!\n";
                return 1;
            }
            pos++;
            buf = argv[pos];
            OutPath = buf;
            continue;
        }

    }

    picture img;
    img.setCS(CS);

    try {
        img.open(InPath, ic);
    }
    catch (std::exception& e) {
        std::cerr<<"File(s) opening has/have been failed!\n";
        std::cerr<<std::endl<<e.what()<<std::endl;
        return 1;
    }

    try{
        img.solve(Conv);
    }
    catch (std::exception& e) {
        std::cerr<<"Image conversion has been failed!\n";
        std::cerr<<std::endl<<e.what()<<std::endl;
        return 1;
    }

    try {
        img.save(OutPath, oc);
    }
    catch (std::exception& e) {
        std::cerr<<"File(s) saving has/have been failed!\n";
        std::cerr<<std::endl<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}
