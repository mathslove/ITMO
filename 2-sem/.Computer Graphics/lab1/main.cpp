#include "pnm.h"

int main(int argc, char* argv[]) {

    //Ошибка кол-ва аргументов
    try{
        if (argc != 4){
            throw std::invalid_argument("");
        }
    }
    catch(std::invalid_argument&) {
        std::cerr<<"\t\tWrong input! Try again.\n\t\tWrong amount of arguments."<<std::endl;
        std::cerr<<"\tInput format:\n"
                   "\t./lab1.exe <input_filename> <output_filename> <command>\n"
                   "\tList of commands:\n"
                   "\t\t0 - color inversion\n"
                   "\t\t1 - mirror horizontally\n"
                   "\t\t2 - mirror vertically\n"
                   "\t\t3 - rotate 90 clockwise\n"
                   "\t\t4 - rotate 90 counter-clockwise"<<std::endl;
        return 1;
    }

    std::string inputPath(argv[1]), outputPath(argv[2]);

    //Ошибка существования фалов
    pnm img;
    try {
        img.read(inputPath);
    }
    catch (std::bad_alloc &){
        std::cerr << "\tWrong input! Try again.\n\tMemory allocation error!"<<std::endl;
        throw std::runtime_error("");
    }
    catch(std::runtime_error&){
        std::cerr << "\tWrong input! Try again.\n\tSomething is \tWrong with file " << inputPath << "!"<<std::endl;
        return 4;
    }

    img.DisplayInfo();

    int command = std::stoi(argv[3]);
    // Ошибка аргумента
    try{
        img.cmd(command);
    }
    catch (std::bad_alloc&){
        std::cerr << "\tWrong input! Try again.\n\tMemory allocation error."<<std::endl;
        return 5;
    }
    catch(std::exception&){
        std::cerr << "\tWrong input! Try again.\n\t\tWrong command."<<std::endl;
        return 3;
    }

    try{
        img.write(outputPath);
    }
    catch (std::ofstream::failure&){
        std::cerr << "\tWrong input! Try again.\n\tFile writing failure."<<std::endl;
        return 5;
    }

    return 0;
}
