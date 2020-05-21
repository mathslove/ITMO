#include "picture.h"

//---------------------//Help methods//---------------------//

void picture::setCS(ColorSpace cs) {
    imgCS = cs;
}

////Image reading
static
std::vector<std::string>
filenames_constructor(const std::string& FILEname){
    std::vector<std::string> filenames(3, FILEname);
    for (size_t i = 0; i < filenames.size(); i++)
        filenames[i].insert(filenames[i].size()-4, "_"+std::to_string(i+1));
    return filenames;
}

static
std::vector<std::ifstream>
ifile_opener3(const std::vector<std::string>& filenames){
    std::vector<std::ifstream> fin(3);
    for (size_t i = 0; i<fin.size(); i++){
        fin[i].open(filenames[i], std::ios::binary);
        fin[i].exceptions(std::ifstream::failbit | std::ifstream::badbit);

        if (!fin[i].is_open())
            throw std::runtime_error("File opening has failed!\n");
    }
    return fin;
}

static
std::vector<std::ofstream>
ofile_opener3(const std::vector<std::string>& filenames){
    std::vector<std::ofstream> fo(3);
    for (size_t i = 0; i<fo.size(); i++){
        fo[i].open(filenames[i], std::ios::binary);
        fo[i].exceptions(std::ofstream::failbit | std::ofstream::badbit);

        if (!fo[i].is_open())
            throw std::runtime_error("File opening has failed!\n");
    }
    return fo;
}

static
void
file_closer3(std::vector<std::ifstream>& f){
    for(auto & ff : f)
        ff.close();
}

static
void
file_closer3(std::vector<std::ofstream>& f){
    for(auto & ff : f)
        ff.close();
}

//---------------------//!Help methods//---------------------//

void
picture::open(const std::string& filename, int count) {
    if (count == 1)
        open_single(filename);
    else if(count ==3)
        open_triple(filename);
    else
        throw std::invalid_argument("Input count is wrong!\n"
                                    "Only 1 or 3 are valid.\n");

}


// Open_single works only for ppm formation!
void
picture::open_single(const std::string &filename) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin.is_open())
        throw std::runtime_error("File opening has failed!\n");

    std::cout<<"\tReading file...\n";
    std::cout<<"\tFrom: "<<filename<<"\n";

    char P;
    fin>>P;
    if (P != 'P')
        throw std::runtime_error("Wrong format of file! Must be PNM!\n");
    fin>>version;
    if ( version != PPM )
        throw std::runtime_error("Wrong format of file! Must be PPM!\n");
    fin>>width>>height;
    fin>>depth;
    fin.get();

    ppm.resize(Size);
    for(size_t i = 0; i<Size; i++){
        fin.get((char&)ppm[i].a);
        fin.get((char&)ppm[i].b);
        fin.get((char&)ppm[i].c);
    }

    fin.close();
    std::cout<<"\tDone.\n\n";
}


// Open_triple works only for pgm formation!
void
picture::open_triple(const std::string& filename) {
    std::vector<std::string> filenames = filenames_constructor(filename);
    std::vector<std::ifstream> fin = ifile_opener3(filenames);

    std::cout << "\tReading file...\n";
    std::cout<<"\tFrom: "<<filenames[0]<<", "<<filenames[1]<<", "<<filenames[2]<<"\n";

    char P;
    std::vector<short> sizes(3);
    for (size_t i = 0; i<fin.size(); i++) {
        fin[i] >> P;
        if (P != 'P')
            throw std::runtime_error("Wrong format of file! Must be PNM!\n");
        fin[i] >> version;
        if (version != PGM)
            throw std::runtime_error("Wrong format of file! Must be PGM!\n");
        fin[i] >> width >> height;
        sizes[i] = Size;
        fin[i] >> depth;
        fin[i].get();
    }

    ppm.resize(Size);

    for (size_t i = 0; i < Size; i++) {
        fin[0].get((char&)ppm[i].a);
        fin[1].get((char&)ppm[i].b);
        fin[2].get((char&)ppm[i].c);
    }

    file_closer3(fin);
    std::cout << "\tDone.\n\n";
}
//!Image reading



//// Image saving
void
picture::save(const std::string& filename, int count) {
    if (count == 1)
        save_single(filename);
    else if(count == 3)
        save_triple(filename);
    else
        throw std::invalid_argument("Input count is wrong!\n"
                                    "Only 1 or 3 are valid.\n");
}

void
picture::save_single(const std::string& filename) {
    std::ofstream fo(filename, std::ios::binary);
    if ( !fo.is_open() )
        throw std::exception();
    std::cout<<"\tWriting image in file...\n";
    std::cout<<"\tTo: "<<filename<<"\n";

    fo.exceptions(std::ofstream::failbit | std::ofstream::badbit);

    fo << "P6" << '\n';
    fo << width << ' ' << height << '\n';
    fo << depth << '\n';

    for (size_t i=0; i<Size; i++) {
        fo<<(( char) ppm[i].a);
        fo<<(( char) ppm[i].b);
        fo<<(( char) ppm[i].c);
    }

    fo.close();
    std::cout<<"\tEverything has been done successfully!\n";
}


void
picture::save_triple(const std::string& filename) {
    std::vector<std::string> filenames = filenames_constructor(filename);
    std::vector<std::ofstream> fo = ofile_opener3(filenames);

    std::cout<<"\tWriting image in file...\n";
    std::cout<<"\tTo: "<<filenames[0]<<", "<<filenames[1]<<", "<<filenames[2]<<"\n";

    for (auto&ff :fo){
        ff << "P5" << '\n';
        ff << width << ' ' << height << '\n';
        ff << depth << '\n';
    }

    for (size_t i=0; i<Size; i++) {
        fo[0]<<(( char) ppm[i].a);
        fo[1]<<(( char) ppm[i].b);
        fo[2]<<(( char) ppm[i].c);
    }

    file_closer3(fo);
    std::cout<<"\tEverything has been done successfully!\n";
}

//!Image saving