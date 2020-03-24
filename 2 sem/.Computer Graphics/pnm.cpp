#include "pnm.h"

#define size width * height

void pnm::DisplayInfo() {
    std::cout<<"\tYour image information:"<<std::endl;
    std::cout<<"\tImage format is P"<<version<<std::endl;
    std::cout<<"\tWidth: "<<width<<"\n\tHeight: "<<height<<std::endl<<"\tColor depth: "<<depth<<std::endl<<std::endl;
}

void pnm::read(const std::string & file) {
    std::ifstream fin(file, std::ios::binary);
    if (!fin.is_open())
        throw std::runtime_error("");
    std::cout<<"\tReading file...\n";
    read(fin);
    fin.close();
    std::cout<<"\tDone.\n\n";
}

void pnm::read(std::ifstream & fin) {
    char P;
    fin>>P;
    if (P != 'P')
        throw std::runtime_error("");
    fin>>version;
    if ( version != PGM && version != PPM )
        throw std::runtime_error("");
    fin>>width>>height;
    fin>>depth;
    version == 5 ? readPGM(fin): readPPM(fin);
}

void pnm::readPGM(std::ifstream& fin) {
    try{
        fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        ppm.clear();
        pgm.resize(size);
        unsigned char tmp;
        for (size_t i = 0; i<size; i++){
            fin.get((char&)tmp);
            pgm[i] = tmp;
        }}
        catch (std::bad_alloc&){
            throw std::bad_alloc();
    }
    catch (std::ifstream::failure&){
        throw std::ifstream::failure("");
    }
}

void pnm::readPPM(std::ifstream& fin) {
    try{
        fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        pgm.clear();
        ppm.resize(size);
        std::string tmp;
        for (size_t i = 0; i<size; i++){
            fin>>(char&)ppm[i].r;
            fin>>(char&)ppm[i].g;
            fin>>(char&)ppm[i].b;
        }
    }
    catch (std::length_error&){
        throw std::bad_alloc();
    }
    catch (std::ifstream::failure&){
        throw std::ifstream::failure("");
    }
}

void pnm::cmd(int command) {
    std::cout<<"\t";
    switch(command) {
        case inversion:
            if (version==PGM)
                inversePGM();
            else
                inversePPM();
            std::cout<<"Inversion completed."<<std::endl;
            break;
        case mirrorHorizontally:
            if (version==PGM)
                mirror_h_PGM();
            else
                mirror_h_PPM();
            std::cout<<"Horizontal mirroring completed."<<std::endl;
            break;
        case mirrorVertically:
            if (version==PGM)
                mirror_v_PGM();
            else
                mirror_v_PPM();
            std::cout<<"Vertical mirroring completed."<<std::endl;
            break;
        case rotate90:
            if (version==PGM)
                rotate90_PGM();
            else
                rotate90_PPM();
            std::cout<<"Image rotation completed."<<std::endl;
            break;
        case rotate270:
            if (version==PGM)
                rotate270_PGM();
            else
                rotate270_PPM();
            std::cout<<"Image rotation completed."<<std::endl;
            break;
        default:
            throw std::exception();
    }
    std::cout<<"\tThe task has been completed successfully!\n "<<std::endl;
}

void pnm::inversePGM() {
    for (size_t i = 0; i<size; i++){
        pgm[i] = depth - pgm[i];
    }
}
void pnm::inversePPM() {
    for (size_t i = 0; i<size; i++){
        ppm[i].r = depth - ppm[i].r;
        ppm[i].g = depth - ppm[i].g;
        ppm[i].b = depth - ppm[i].b;
    }
}

void pnm::mirror_v_PGM() {
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width / 2; ++j)
            std::swap(pgm[i * width + j],
                      pgm[i * width + width - j - 1]);
}

void pnm::mirror_v_PPM() {
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width / 2; ++j)
            std::swap(ppm[i * width + j],
                      ppm[i * width + width - j - 1]);
}

void pnm::mirror_h_PGM() {
    for (size_t j = 0; j < width; ++j)
        for (size_t i = 0; i < height / 2; ++i)
            std::swap(pgm[i * width + j],
                      pgm[(height - 1) * width - i * width + j]);
}

void pnm::mirror_h_PPM() {
    for (size_t j = 0; j < width; ++j)
        for (size_t i = 0; i < height / 2; ++i)
            std::swap(ppm[i * width + j],
                      ppm[(height - 1) * width - i * width + j]);
}

void pnm::rotate90_PGM() {
    try {
        std::vector<unsigned char> tmp(size);
        for (size_t i = 0; i < width; i++)
            for (size_t j = 0; j < height; j++)
                tmp[i * height + j] = pgm[(height - j - 1) * width + i];
        pgm.clear();
        pgm = tmp;
        std::swap(height, width);
    }
    catch (std::bad_alloc&){
        throw std::bad_alloc();
    }
}

void pnm::rotate90_PPM() {
    try {
        std::vector<RGB> tmp(size);
        for (size_t i = 0; i < width; i++)
            for (size_t j = 0; j < height; j++)
                tmp[i * height + j] = ppm[(height - j - 1) * width + i];
        ppm.clear();
        ppm = tmp;
        std::swap(height, width);
    }
    catch (std::bad_alloc&){
        throw std::bad_alloc();
    }
}

void pnm::rotate270_PGM() {
    try{
    std::vector<unsigned char> tmp(size);
    for (size_t i = 0; i < width; i++)
        for (size_t j = 0; j < height; j++)
            tmp[i*height+j] = pgm[j*width+i];
    pgm.clear();
    pgm = tmp;
    std::swap(height, width);}
    catch (std::bad_alloc&){
        throw std::bad_alloc();
    }
}

void pnm::rotate270_PPM() {
    try{
    std::vector<RGB> tmp(size);
    for (size_t i = 0; i < width; i++)
        for (size_t j = 0; j < height; j++)
            tmp[i*height+j] = ppm[j*width+i];
    ppm.clear();
    ppm = tmp;
    std::swap(height, width);}
    catch (std::bad_alloc&){
        throw std::bad_alloc();
    }
}

void pnm::write(std::string& file) {
    std::ofstream fo(file, std::ios::binary);
    if ( !fo.is_open() )
        throw std::exception();
    std::cout<<"\tWriting image in file...\n";
    write(fo);
    fo.close();
    std::cout<<"\tEverything has been done succesfully!\n";
}

void pnm::write(std::ofstream& file) {
    file << "P" << version << '\n';
    file << width << ' ' << height << '\n';
    file << depth << '\n';
    version == 5 ? writePGM(file) : writePPM(file);
}

void pnm::writePGM(std::ofstream& file) {
    try {
        file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        for (size_t i = 0; i < size; i++)
            file.put((char &) pgm[i]);
        pgm.clear();
    }
    catch (std::ofstream::failure&){
        throw std::ofstream::failure("");
    }
}

void pnm::writePPM(std::ofstream& file) {
    try
    {
        file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        for (size_t i=0; i<size; i++){
        file.put((char)ppm[i].r);
        file.put((char)ppm[i].g);
        file.put((char)ppm[i].b);
    }
    ppm.clear();}
    catch (std::bad_alloc&){
        throw std::bad_alloc();
    }
    catch (std::ofstream::failure&){
        throw std::ofstream::failure("");
    }
}