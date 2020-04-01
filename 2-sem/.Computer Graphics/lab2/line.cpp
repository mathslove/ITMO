#include "logic.h"

int pnm::ipart(double a) {
    return (int)a;
}

int pnm::round(double a) {
    return std::round(a);
}


void pnm::plot(bool swaped,int x, int y, double brightness, float r_brightness, float g) {
    if (y < 0 || y >= height || x < 0 || x >= width)
        return;
    brightness = std::max(std::min(brightness, 1.0), 0.0);
    if (swaped) std::swap(x, y);
    if (g!=0) {
        pgm[y][x] = 255 * pow((brightness * pgm[y][x] + r_brightness * (1 - brightness)) / 255.0,(1.0 / g - 1.0) * (1.0 - brightness) + 1.0);
    } else{
        double lineClrLin = r_brightness / 255.0;
        double picClrSRGB = pgm[y][x] / 255.0;
        double picColorLinear = picClrSRGB <= 0.04045 ? picClrSRGB / 12.92 : pow((picClrSRGB + 0.055) / 1.055, 2.4);
        double c_Linear = (1 - brightness) * lineClrLin + brightness * picColorLinear;
        double c_sRGB = c_Linear <= 0.0031308 ? 12.92 * c_Linear : 1.055 * pow(c_Linear, 1 / 2.4) - 0.055;
        pgm[y][x] = llround(255 * c_sRGB);
    }
}

void pnm::DrawLine(float& x0, float& y0, float& x1, float& y1,
                   float& thickness, unsigned short& brightness, float gamma)
{
    if (thickness<0) return;

    bool steep = fabsf(y1-y0) > fabsf(x1-x0);

    if (steep)
    {
        std::swap(x0, y0);
        std::swap(x1 , y1);
    }

    if (x0 > x1)
    {
        std::swap(x0 ,x1);
        std::swap(y0 ,y1);
    }

    float dx = x1-x0;
    float dy = y1-y0;
    float gradient = dy/dx;
    double y = y0 + gradient * (round(x0) - x0);

    for (int x = (int)round(x0); x <= (int)round(x1); ++x) {
        for (int plotY = ipart(y - (thickness - 1) / 2);
             plotY <= ipart(y - (thickness - 1) / 2 + thickness); ++plotY) {
            plot(steep, x, plotY,
                 1 - std::min(1.0, (thickness + 1.0) / 2.0 - fabs(y - plotY)), brightness, gamma);
        }
        y += gradient;
    }

    for (int xT = (int)(round(x0)-thickness / 2); xT <= (int)round(x0);xT++){
        y = y0+gradient*((double)xT-x0);
        for (int yT = y - (thickness-1)/2; yT<=y - (thickness-1)/2+thickness; yT++)
            plot(steep, xT, yT, 1 - std::min(1.0,(thickness + 1.0) / 2.0 - sqrt(pow(x0-xT,2)+pow(y0-yT,2)) ), brightness, gamma);
    }

    for (int xT = ipart(x1); xT <= (int)((double)ipart(x1)+thickness / 2) ;xT++){
        y = y1+gradient*((double)xT-x1);
        for (int yT = y - (thickness-1)/2; yT<=y - (thickness-1)/2+thickness; yT++)
            plot(steep, xT, yT, 1 - std::min(1.0,(thickness + 1.0) / 2.0 - sqrt(pow(x1-xT,2)+pow(y1-yT,2)) ), brightness, gamma);
    }
}
