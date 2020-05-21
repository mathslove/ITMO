#include <cmath>
#include "picture.h"

//// Helep
static
std::string
CSname(ColorSpace CS){
    std::string name;
    switch (CS) {
        case RGB:
            name = "RGB";
            break;
        case HSL:
            name = "HSL";
            break;
        case HSV:
            name = "HSV";
            break;
        case YCbCr601:
            name = "YCbCr.601";
            break;
        case YCbCr709:
            name = "YCbCr.709";
            break;
        case YCoCg:
            name = "YCoCg";
            break;
        case CMY:
            name = "CMY";
            break;
    }
    return name;
}
//!

void
picture::solve(ColorSpace newCS){
    std::cout << "\tSolving in process...\n";
    std::string inputCS = CSname(imgCS), outputCS = CSname(newCS);
    if (imgCS == newCS)
        return;

    toRgb();

    double Max, Min, H, S, L, C, V, M;
    double Y, Cb, Cr, Co, Cg, Kr, Kg, Kb, R, G, B;

    switch (newCS) {
        case HSV:
            for (size_t i = 0; i < Size; i++){
                R = ppm[i].a/255.00;
                G = ppm[i].b/255.00;
                B = ppm[i].c/255.00;

                Max = std::max(std::max(R,G),B);
                Min = std::min(std::min(R,G),B);
                double d = Max-Min;

                if (d == 0)
                    H = 0;
                else if (Max == R)
                    H = 60.0*std::fmod((G-B)/d,6);
                else if (Max == G)
                    H = 60.0*((B-R)/d+2.);
                else if (Max == B)
                    H = 60.*((R-G)/d+4.);

                S = (Max == 0? 0: d/Max);
                V = Max;

                ppm[i].a = static_cast< char>(std::round(H/360.0*255.0));
                ppm[i].b = static_cast< char>(std::round(S*255.0));
                ppm[i].c = static_cast< char>(std::round(V*255.0));
            }
            break;
        case HSL:
            for (size_t i = 0; i < Size; i++){
                R = ppm[i].a/255.0;
                G = ppm[i].b/255.0;
                B = ppm[i].c/255.0;

                Max = std::max(std::max(R,G),B);
                Min = std::min(std::min(R,G),B);
                double d = Max-Min;

                if (d == 0)
                    H = 0;
                else if (Max == R)
                    H = 60.0*std::fmod((G-B)/d,6);
                else if (Max == G)
                    H = 60.0*((B-R)/d+2.);
                else if (Max == B)
                    H = 60.*((R-G)/d+4.);

                L = (Max+Min)/2.0;
                S = (Max == 0? 0: d/(1.-fabs(2.*L-1.)));

                ppm[i].a = static_cast< char>(std::round(H/360.0*255.0));
                ppm[i].b = static_cast< char>(std::round(S*255.0));
                ppm[i].c = static_cast< char>(std::round(L*255.0));
            }
            break;
        case YCbCr601:
            Kr = 0.299;
            Kg = 0.587;
            Kb = 0.114;

            for (size_t i = 0; i < Size; i++)
            {
                R = ppm[i].a / 255.0;
                G = ppm[i].b / 255.0;
                B = ppm[i].c / 255.0;
                Y = Kr * R + Kg * G + Kb * B;
                Cb = 0.5 * ((B - Y) / (1.0 - Kb));
                Cr = 0.5 * ((R - Y) / (1.0 - Kr));
                ppm[i].a = static_cast< char >(Y * 255.0);
                ppm[i].b = static_cast< char >((Cb + 0.5)*255.0);
                ppm[i].c = static_cast< char >((Cr + 0.5)*255.0);
            }
            break;
        case YCbCr709:
            Kr = 0.0722;
            Kg = 0.2126;
            Kb = 0.7152;
            for (int i = 0; i < Size; i++){
                R = ppm[i].a / 255.0;
                G = ppm[i].b / 255.0;
                B = ppm[i].c / 255.0;
                Y = Kr * R + Kg * G + Kb * B;
                Cb = 0.5 * ((B - Y) / (1.0 - Kb));
                Cr = 0.5 * ((R - Y) / (1.0 - Kr));
                ppm[i].a = static_cast< char>(Y * 255.0);
                ppm[i].b = static_cast< char>((Cb + 0.5)*255.0);
                ppm[i].c = static_cast< char>((Cr + 0.5)*255.0);
            }
            break;
        case YCoCg:
            for (size_t i = 0; i < Size; i++) {
                R = ppm[i].a / 255.0;
                G = ppm[i].b / 255.0;
                B = ppm[i].c / 255.0;
                Y = R / 4 + G / 2 + B / 4;
                Co = R / 2 - B / 2;
                Cg = -R / 4 + G / 2 - B / 4;
                ppm[i].a = static_cast< char>(Y * 255.0);
                ppm[i].b = static_cast< char>((Co + 0.5) * 255.0);
                ppm[i].c = static_cast< char>((Cg + 0.5) * 255.0);
            }
            break;
        case CMY:
            for (size_t i = 0; i < Size; i++) {
                R = ppm[i].a / 255.0;
                G = ppm[i].b / 255.0;
                B = ppm[i].c / 255.0;
                C = 1 - R;
                M = 1 - G;
                Y = 1 - B;
                ppm[i].a = static_cast< char>(C * 255.0);
                ppm[i].b = static_cast< char>(M  * 255.0);
                ppm[i].c = static_cast< char>(Y * 255.0);
            }
            break;
        case RGB:
            break;
    }

    std::cout << "\tYour image color space has been successfully changed\n"
                 "\tFrom: "<<inputCS<<"\n\tTo:   "<<outputCS<<"\n\n";
    imgCS = newCS;
}


void
picture::toRgb() {
    if (imgCS == RGB)
        return;

    double H, S, L, C, V, X, m, R, G, B, Y, Cb, Cr, Co, Cg, M, Kr, Kg, Kb;

    switch (imgCS) {
        case HSV:
            for (size_t i = 0; i < Size; i++){
                H = (ppm[i].a / 255.00) * 360.00;
                S = ppm[i].b / 255.00;
                V = ppm[i].c / 255.00;

                C = V * S;
                X = C * (1.0 - fabs(fmod((H/60.0),2) - 1.0));
                m = V - C;

                if (H>=0.0 && H < 60.0){
                    R = C;
                    G = X;
                    B = 0;
                } else if (H>=60 && H < 120.){
                    R = X;
                    G = C;
                    B = 0;
                } else if (H>=120 && H < 180.){
                    R = 0;
                    G = C;
                    B = X;
                } else if (H>=180 && H < 240.){
                    R = 0;
                    G = X;
                    B = C;
                } else if (H>=240 && H < 300.){
                    R = X;
                    G = 0;
                    B = C;
                } else if (H>=300 && H < 360.0){
                    R = C;
                    G = 0;
                    B = X;
                }

                ppm[i].a = static_cast< char>(std::round((R+m)*255.0));
                ppm[i].b = static_cast< char>(std::round((G+m)*255.0));
                ppm[i].c = static_cast< char>(std::round((B+m)*255.0));
            }
            break;
        case HSL:
            for (size_t i = 0; i < Size; i++){
                H = (ppm[i].a / 255.0) * 360.0;
                S = ppm[i].b / 255.0;
                L = ppm[i].c / 255.0;

                C = (1.0-fabs(2.0*L-1.0))*S;
                X = C * (1.0 - fabs(fmod((H/60.0),2) - 1.0));
                m = L - C/2.0;

                if (H>=0.0 && H < 60.0){
                    R = C;
                    G = X;
                    B = 0;
                } else if (H>=60 && H < 120.){
                    R = X;
                    G = C;
                    B = 0;
                } else if (H>=120 && H < 180.){
                    R = 0;
                    G = C;
                    B = X;
                } else if (H>=180 && H < 240.){
                    R = 0;
                    G = X;
                    B = C;
                } else if (H>=240 && H < 300.){
                    R = X;
                    G = 0;
                    B = C;
                } else if (H>=300 && H < 360.0){
                    R = C;
                    G = 0;
                    B = X;
                }

                ppm[i].a = static_cast< char>(std::round((R+m)*255.0));
                ppm[i].b = static_cast< char>(std::round((G+m)*255.0));
                ppm[i].c = static_cast< char>(std::round((B+m)*255.0));
            }
            break;
        case YCbCr601:
            Kr = 0.299;
            Kg = 0.587;
            Kb = 0.114;
            for (size_t i = 0; i < Size; i++) {
                Y = ppm[i].a / 255.0;
                Cb = (ppm[i].b / 255.0) - 0.5;
                Cr = (ppm[i].c / 255.0) - 0.5;
                R = (Y + Cr * (2.0 - 2.0 * Kr));
                G = (Y - (Kb / Kg) * (2.0 - 2.0 * Kb) * Cb - (Kr / Kg) * (2.0 - 2.0 * Kr) * Cr);
                B = (Y + (2.0 - 2.0 * Kb) * Cb);
                if (R < 0) R = 0;
                if (G < 0) G = 0;
                if (B < 0) B = 0;
                if (R > 1) R = 1;
                if (G > 1) G = 1;
                if (B > 1) B = 1;
                ppm[i].a = static_cast< char >(R * 255.0);
                ppm[i].b = static_cast< char >(G * 255.0);
                ppm[i].c = static_cast< char >(B * 255.0);
            }
            break;
        case YCbCr709:
            Kr = 0.0722;
            Kg = 0.2126;
            Kb = 0.7152;
            for (int i = 0; i < Size; i++) {
                Y = ppm[i].a / 255.0;
                Cb = (ppm[i].b / 255.0) - 0.5;
                Cr = (ppm[i].c / 255.0) - 0.5;
                R = (Y + Cr * (2.0 - 2.0 * Kr));
                G = (Y - (Kb / Kg) * (2.0 - 2.0 * Kb) * Cb - (Kr / Kg) * (2.0 - 2.0 * Kr) * Cr);
                B = (Y + (2.0 - 2.0 * Kb) * Cb);
                if (R < 0) R = 0;
                if (G < 0) G = 0;
                if (B < 0) B = 0;
                if (R > 1) R = 1;
                if (G > 1) G = 1;
                if (B > 1) B = 1;
                ppm[i].a = static_cast< char>(R * 255.0);
                ppm[i].b = static_cast< char>(G * 255.0);
                ppm[i].c = static_cast< char>(B * 255.0);
            }
            break;
        case YCoCg:
            for (size_t i = 0; i < Size; i++) {
                Y = ppm[i].a / 255.0;
                Co = (ppm[i].b / 255.0) - 0.5;
                Cg = (ppm[i].c / 255.0) - 0.5;
                R = Y + Co - Cg;
                G = Y + Cg;
                B = Y - Co - Cg;
                if (R < 0) R = 0;
                if (G < 0) G = 0;
                if (B < 0) B = 0;
                if (R > 1) R = 1;
                if (G > 1) G = 1;
                if (B > 1) B = 1;
                ppm[i].a = static_cast< char>(R * 255.0);
                ppm[i].b = static_cast< char>(G * 255.0);
                ppm[i].c = static_cast< char>(B * 255.0);
            }
            break;
        case CMY:
            for (size_t i = 0; i < Size; i++) {
                C = ppm[i].a / 255.0;
                M = ppm[i].b / 255.0;
                Y = ppm[i].c / 255.0;
                R = 1 - C;
                G = 1 - M;
                B = 1 - Y;
                ppm[i].a = static_cast< char>(R * 255.0);
                ppm[i].b = static_cast< char>(G * 255.0);
                ppm[i].c = static_cast< char>(B * 255.0);
            }
            break;
        case RGB:
            break;
    }
    imgCS = RGB;
}

//  Источники:
//      https://www.rapidtables.com/convert/color/
//      https://en.wikipedia.org/wiki/