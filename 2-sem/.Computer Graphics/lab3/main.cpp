#include "logic.h"

int main(int argc, char* argv[]) {
    if (argc != 7){
        std::cerr<<"\n\tWrong amount of arguments!\n"
                   "\tExpected format:\n"
                   "\tlab3.exe <input filename> <output filename> <gradient> <dithering> <bitness> <gamma>\n";
        return 1;
    }

    std::string inPath = argv[1], outPath = argv[2];

    static int gradient = std::stoi(argv[3]);
    try {
        if (gradient != 0 && gradient != 1) throw std::invalid_argument("stupid");
    }
    catch (std::invalid_argument&){
        std::cerr<<"\tWrong argument!\n\tArgument number 3 must be 0 or 1.\n";
        return 1;
    }

    static int dithering = std::stoi(argv[4]);
    try {
        if (dithering < 0 || dithering > 7) throw std::invalid_argument("stupid");
    }
    catch (std::invalid_argument&){
        std::cerr<<"\tWrong argument!\n\tArgument number 4 must be between 0 and 7.\n";
        return 1;
    }

    static int bitness = std::stoi(argv[5]);
    try {
        if (bitness < 1 || bitness > 8) throw std::invalid_argument("stupid");
    }
    catch (std::invalid_argument&){
        std::cerr<<"\tWrong argument!\n\tArgument number 5 must be between 1 and 8.\n";
        return 1;
    }

    static double gamma = std::stod(argv[6]);
    try {
        if (gamma < 0) throw std::invalid_argument("stupid");
    }
    catch (std::invalid_argument&){
        std::cerr<<"\tWrong argument!\n\tArgument number 6 cant't be less than 0\n";
        return 1;
    }
    pnm img(gamma);

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

    img.auto_gradient(gradient);

    try {
        img.dithering(dithering, bitness);
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
