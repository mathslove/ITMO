//
// Created by mmas6 on 27.03.2020.
//

#ifndef LAB3_LOGIC_H
#define LAB3_LOGIC_H

#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

enum Image_t{
    PGM = 5
};

enum Dither{
    no = 0,
    ordered,
    random,
    Floyd_Steinberg,
    Jarvis_Judice_Ninke,
    Sierra,
    Atkinson,
    Halftone,
};

const double ORDERED_MATRIX[8][8] =
        {
            {0. / 64.,  48. / 64., 12. / 64., 60. / 64., 3. / 64.,  51. / 64., 15. / 64., 63. / 64.},
            {32. / 64., 16. / 64., 44. / 64., 28. / 64., 35. / 64., 19. / 64., 47. / 64., 31. / 64.},
            {8. / 64.,  56. / 64., 4. / 64.,  52. / 64., 11. / 64., 59. / 64., 7. / 64.,  55. / 64.},
            {40. / 64., 24. / 64., 36. / 64., 20. / 64., 43. / 64., 27. / 64., 39. / 64., 23. / 64.},
            {2. / 64.,  50. / 64., 14. / 64., 62. / 64., 1. / 64.,  49. / 64., 13. / 64., 61. / 64.},
            {34. / 64., 18. / 64., 46. / 64., 30. / 64., 33. / 64., 17. / 64., 45. / 64., 29. / 64.},
            {10. / 64., 58. / 64., 6. / 64.,  54. / 64., 9. / 64.,  57. / 64., 5. / 64.,  53. / 64.},
            {42. / 64., 26. / 64., 38. / 64., 22. / 64., 41. / 64., 25. / 64., 37. / 64., 21. / 64.}
        };

const double JJN_MATRIX[3][5] =
        {
            {0, 0, 0, 7, 5},
            {3, 5, 7, 5, 3},
            {1, 3, 5, 3, 1}
        };

const double SIERRA3_MATRIX[3][5] =
        {
            {0, 0, 0, 5, 3},
            {2, 4, 5, 4, 2},
            {0, 2, 3, 2, 0}
        };

const double ATKINSON_MATRIX[3][5] =
        {
            {0, 0, 0, 1, 1},
            {0, 1, 1, 1, 0},
            {0, 0, 1, 0, 0}
        };

const double HALFTONE_MATRIX[4][4] =
        {
            {13. / 16, 11. / 16, 4. / 16,  8. / 16},
            {6. / 16,  0,         3. / 16,  15. / 16},
            {14. / 16, 1. / 16,  2. / 16,  7. / 16},
            {9. / 16,  5. / 16,  10. / 16, 12. / 16},
        };

class pnm{
private:
    std::vector<std::vector<unsigned char>> pgm;
    short version;
    size_t width, height, depth;
    double gamma;

    void read(std::ifstream&);
    void write(std::ofstream&);

    double correct(double);
    double reverse_correct(double);

    void noDither(int);
    void Ordered(int);
    void Random(int);
    void FS(int);
    void JJN(int);
    void A(int);
    void _Sierra(int);
    void _Halftone(int);

public:
    pnm(double g){
        gamma = g;
    };

    void read(const std::string&);
    void DisplayInfo();
    void write(const std::string&);

    void auto_gradient(bool);
    void dithering(int, int);


};


#endif //LAB3_LOGIC_H
