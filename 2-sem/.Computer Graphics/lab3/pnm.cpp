//
// Created by mmas6 on 27.03.2020.
//

#include "logic.h"

void pnm::DisplayInfo() {
    std::cout << "\tYour image information:" << std::endl;
    std::cout << "\tImage format is P" << version << std::endl;
    std::cout << "\tWidth: " << width << "\n\tHeight: " << height << std::endl << "\tColor depth: " << depth
              << std::endl << std::endl;
}

void pnm::read(const std::string &file) {
    std::ifstream fin(file, std::ios::binary);
    if (!fin.is_open())
        throw std::runtime_error("");
    std::cout << "\tReading file...\n";
    read(fin);
    fin.close();
    std::cout << "\tDone.\n\n";
}

void pnm::read(std::ifstream &fin) {
    try {
        fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        char P;
        fin >> P;
        if (P != 'P')
            throw std::runtime_error("");
        fin >> version;
        if (version != PGM)
            throw std::runtime_error("");
        fin >> width >> height;
        fin >> depth;
        fin.get();
        pgm.resize(height);
        unsigned char tmp;
        for (size_t i = 0; i < height; i++) {
            pgm[i].resize(width);
            for (size_t j = 0; j < width; j++) {
                fin.get((char &) tmp);
                pgm[i][j] = tmp;
            }
        }
    }

    catch (std::ifstream::failure &) {
        throw std::ofstream::failure("");
    }

    catch (std::bad_alloc &) {
        throw std::bad_alloc();
    }
}

void pnm::write(const std::string &file) {
    std::ofstream fo(file, std::ios::binary);
    if (!fo.is_open())
        throw std::exception();
    std::cout << "\tWriting image in file...\n";
    write(fo);
    fo.close();
    std::cout << "\tEverything has been done succesfully!\n";
}

void pnm::write(std::ofstream &fo) {
    try {
        fo << "P" << version << '\n';
        fo << width << ' ' << height << '\n';
        fo << depth << '\n';

        fo.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        for (size_t i = 0; i < height; i++)
            for (size_t j = 0; j < width; j++)
                fo.put((char &) pgm[i][j]);
        pgm.clear();
    }
    catch (std::ofstream::failure &) {
        throw std::ofstream::failure("");
    }
}

