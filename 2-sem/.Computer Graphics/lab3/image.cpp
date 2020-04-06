//
// Created by mmas6 on 27.03.2020.
//

#include "logic.h"

double pix(double val){
    if (val>255)
        return 255;
    if (val<0)
        return 0;
    return val;
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double pnm::correct(double val) {
    val/=depth;
    val>1?val=1:val;
    val<0?val=0:val;
    if (gamma==0)
        return (val < 0.0031308 ? depth*val*12.92: depth*(211.0 * pow(val, 0.4166) - 11.0) / 200.0);
    else
        return round(depth * pow(val, gamma));
}

double pnm::reverse_correct(double val) {
    val/=255;
    if (gamma==0)
        return (val<0.04045? 255*val/12.92: 255*pow((200.0 * val + 11.0) / 211.0, 2.4));
    else
        return 255 * pow(val, 1/gamma);
}

void pnm::auto_gradient(bool f) {
    if (!f) return;
    for (size_t y = 0; y < height;y++)
        for (size_t x = 0;x < width;x++){
            pgm[y][x] = correct((double)x/width*255);
        }
}

void pnm::dithering(int type, int bit) {
    switch (type){
        case no:
            noDither(bit);
            break;
        case ordered:
            Ordered(bit);
            break;
        case random:
            Random(bit);
            break;
        case Floyd_Steinberg:
            FS(bit);
            break;
        case Jarvis_Judice_Ninke:
            JJN(bit);
            break;
        case Sierra:
            _Sierra(bit);
            break;
        case Atkinson:
            A(bit);
            break;
        case Halftone:
            _Halftone(bit);
            break;
    }
}

void pnm::noDither(int bit) {
    int newDepth = (int)pow(2, bit)-1;
    double buf;
    depth = newDepth;
    for(size_t y = 0; y<height;y++)
        for (size_t x = 0; x<width; x++){
            buf = (reverse_correct(pgm[y][x]))/255;
            buf = round(buf*newDepth);
            pgm[y][x] = correct(buf);
    }
}

void pnm::Ordered(int bit) {
    int newDepth = (int)pow(2, bit)-1;
    double buf;
    depth = newDepth;
    for(size_t y = 0; y<height;y++)
        for (size_t x = 0; x<width; x++){
            buf =  (reverse_correct(pgm[y][x])+(255.)*(ORDERED_MATRIX[y % 8][x % 8] - 0.5))/255;
            buf = round(buf*newDepth);
            pgm[y][x] = correct(buf);
        }
}

void pnm::Random(int bit) {
    srand(time(nullptr));
    int newDepth = (int)pow(2, bit)-1;
    double buf;
    depth = newDepth;
    for(size_t y = 0; y<height;y++)
        for (size_t x = 0; x<width; x++){
            buf =  reverse_correct(pgm[y][x])/255+fRand(-.2, .2);
            buf = round(buf*newDepth);
            pgm[y][x] = correct(buf);
        }
}

void pnm::FS(int bit) {
    int newDepth = (int)pow(2, bit)-1;
    double buffer, currentError;
    std::vector<double> errors;
    errors.resize(width*height, 0);
    depth = newDepth;
    for (auto i = 0; i < height; ++i)
        for (auto j = 0; j < width; ++j)
        {
            buffer = (reverse_correct(pgm[i][j])
                      + errors[i * width + j]) / 255;
            buffer = round(buffer*newDepth);
            currentError = pgm[i][j] + errors[i * width + j] - buffer*(255. / newDepth);
            pgm[i][j] = correct(buffer);
            if (j!=width-1)
                errors[i * width + j + 1] += currentError * (7. / 16.);
            if (i!=height-1)
            {
                if (j!=width-1)
                    errors[(i + 1) * width + j + 1] += currentError * (1. / 16.);
                errors[(i + 1) * width + j] += currentError * (5. / 16.);
                if (i!=0 && j!=0)
                    errors[(i - 1) * width + j - 1] += currentError * (3. / 16.);
            }
        }
}

void pnm::JJN(int bit) {
        int newDepth = (int)pow(2, bit)-1;
        double buffer, currentError;
        std::vector<double> errors;
        errors.resize(width*height, 0);
        depth = newDepth;
        for (auto y = 0; y < height; ++y)
            for (auto x = 0; x < width; ++x)
            {
                buffer = (reverse_correct(pgm[y][x])
                          + errors[y * width + x]) /255;
                buffer *= newDepth;
                buffer = round(buffer);
                currentError = pgm[y][x] + errors[y *width + x] - buffer*(255. / newDepth);
                pgm[y][x] = correct(buffer);
                for (auto k = 0; k <= 2; ++k)
                    for (auto l = -2; l <= 2; ++l)
                        if (y + k < height)
                        {
                            if ( k == 0 && l > 0)
                            {
                                if (x + l < width)
                                    errors[(y + k) * width + x + l] += currentError * JJN_MATRIX[k][2 + l] / 48.;
                            }
                            else
                                if (x + l < width && x + l > 0)
                                    errors[(y + k) * width + x + l] += currentError * JJN_MATRIX[k][2 + l] / 48.;
                        }
            }
}

void pnm::A(int bit) {
    int newDepth = pow(2, bit)-1;
    double buffer, currentError;;
    std::vector<double> errors;
    errors.resize(width*height, 0);
    depth = newDepth;
    for (auto i = 0; i < height; ++i)
        for (auto j = 0; j < width; ++j)
        {
            buffer = (reverse_correct(pgm[i][j]) + errors[i * width + j]) / 255;
            buffer *= newDepth;
            buffer = round(buffer);
            currentError = pgm[i][j] + errors[i * width + j] - buffer*(255. / newDepth);
            pgm[i][j] = correct(buffer);
            for (auto k = 0; k <= 2; ++k)
                for (auto l = -2; l <= 2; ++l)
                    if (i + k < height)
                    {
                        if ( k == 0 && l > 0 )
                        {
                            if (j + l < width)
                                errors[(i + k) * width + j + l] += currentError * ATKINSON_MATRIX[k][2 + l] / 8.;
                        }
                        else
                        {
                            if (j + l < width && j + l > 0)
                                errors[(i + k) * width + j + l] += currentError * ATKINSON_MATRIX[k][2 + l] / 8.;
                        }
                    }
        }
}

void pnm::_Sierra(int bit) {
    int newDepth = pow(2, bit)-1;
    double buffer, currentError;;
    std::vector<double> errors;
    errors.resize(width*height, 0);
    depth = newDepth;
    for (auto i = 0; i < height; ++i)
        for (auto j = 0; j < width; ++j)
        {
            buffer = (reverse_correct(pgm[i][j]) + errors[i * width + j]) / 255;
            buffer *= newDepth;
            buffer = round(buffer);
            currentError = pgm[i][j] + errors[i * width + j] - buffer*(255. / newDepth);
            pgm[i][j] = correct(buffer);
            for (auto k = 0; k <= 2; ++k)
                for (auto l = -2; l <= 2; ++l)
                    if (i + k < height)
                    {
                        if ( k == 0 && l > 0 )
                        {
                            if (j + l < width)
                                errors[(i + k) * width + j + l] += currentError * SIERRA3_MATRIX[k][2 + l] / 32.;
                        }
                        else
                        {
                            if (j + l < width && j + l > 0)
                                errors[(i + k) * width + j + l] += currentError * SIERRA3_MATRIX[k][2 + l] / 32.;
                        }
                    }
        }

}

void pnm::_Halftone(int bit) {
    int newDepth = (int)pow(2, bit)-1;
    double buffer;
    depth = newDepth;
    for (auto i = 0; i < height; ++i)
        for (auto j = 0; j < width; ++j)
        {
            buffer = (reverse_correct(pgm[i][j])
                      + 255./newDepth*(HALFTONE_MATRIX[i % 4][j % 4] - 0.75) ) / 255;
            buffer = round(buffer*newDepth);
            pgm[i][j] = correct(buffer);
        }
}

