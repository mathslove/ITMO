#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dir.h>

void Life(int** life, int hei, int wid) {
    int count;
    int** tmp = (int**)malloc(sizeof(int*) * hei);
    for (int i = 0; i < hei; ++i) {
        tmp[i] = (int*)malloc(sizeof(int) * wid);
    }
    int x, y;
    int inf = 0;
    for (y = 0; y < hei; y++)
        for (x = 0; x < wid; x++)
            tmp[y][x] = life[y][x];
    for (y = 1; y < hei - 1; y++) {
        for (x = 1; x < wid - 1; x++) {
            count = life[y + 1][x - 1] + life[y + 1][x] + life[y + 1][x + 1] + life[y][x - 1] + life[y][x + 1] + life[y - 1][x - 1] + life[y - 1][x] + life[y - 1][x + 1];
            if (tmp[y][x] == 1) {
                if (count == 2) tmp[y][x] = life[y][x];
                if (count == 3) tmp[y][x] = life[y][x];
                if (count > 3) tmp[y][x] = 0;
                if (count < 2) tmp[y][x] = 0;
            }
            else {
                if (count == 3) tmp[y][x] = 1;
            }
            count = 0;
        }
    }
    for (y = 0; y < hei; y++)
        for (x = 0; x < wid; x++) {
            if (life[y][x] == tmp[y][x])
                inf++;
            life[y][x] = tmp[y][x];
        }
    for (int i = 0; i < hei; ++i) {
        free(tmp[i]);
    }
    free(tmp);
    if (inf == hei * wid)
        exit(0);
}

struct BMP {
    int Width;
    int Height;
    int Size;
};

int main(int argc, char* argv[]){
    struct BMP Image;
    FILE* file = NULL;
    char* dirname = NULL;
    int maxiter = INT_MAX;
    int dumpfreq = 1;
    int i,j,k,l,m;
    unsigned char header[54];

    // Читаем консоль
    for (i = 1; i < argc; i++){
        if (!strcmp("--input", argv[i])){
            file = fopen(argv[i+1], "rb");
        }
        if (!strcmp("--output", argv[i])){
            dirname = argv[i+1];
            mkdir(dirname);
        }
        if (!strcmp("--max_iter", argv[i])) {
            maxiter = strtol(argv[i + 1], 0, 10);
        }
        if (!strcmp("--dump_freq", argv[i])) {
            dumpfreq = strtol(argv[i + 1], 0, 10);
        }
    }

//    file = fopen("world.bmp", "rb");
//    dirname = "Test";
//    mkdir(dirname);
//    maxiter = 5;
    //Считаем изображение
    fread(header, sizeof(unsigned char), 54, file);
    Image.Width = header[21] * 256 * 256 * 256 + header[20] * 256 * 256 + header[19] * 256 + header[18];
    Image.Height = header[25] * 256 * 256 * 256 + header[24] * 256 * 256 + header[23] * 256 + header[22];
    Image.Size = header[5] * 256 * 256 * 256 + header[4] * 256 * 256 + header[3] * 256 + header[2];
    unsigned char Imagebyte[Image.Size - 54];
    fread(Imagebyte, sizeof(unsigned char), Image.Size, file);

    int** world = (int**)malloc(Image.Height * sizeof(int*));
    for(int i = 0; i < Image.Height; i++)
        world[i] = (int*)malloc(Image.Width * sizeof(int));

    k = 0;
    for(int i = Image.Height - 1; i >= 0; i--){

        for(int j = 0; j < Image.Width; j++){
            if(Imagebyte[k] == 255)
                world[i][j] = 0;
            else
                world[i][j] = 1;
            k += 3;
        }
    }

    // Игра жизнь
    for (l = 1; l <= maxiter; l++) {
        Life(world, Image.Height, Image.Width);

        if (l % dumpfreq != 0) continue;

        // Создаём новое название новому файла
        char path[256];
        char filename[16];
        strcpy(path, dirname);
        strcat(path, "\\");
        strcat(path, _itoa(l, filename, 10));
        strcat(path, ".bmp");
        FILE* life = fopen(path, "wb");
        fwrite(header, 1, 54, life);
        m = 0;

        // Создаём новую картинку
        for (i = Image.Height - 1; i >= 0; i--) {
            for (j = 0; j < Image.Width; j++) {
                for (k = 0; k < 3; k++) {
                    if (world[i][j] == 1)
                        Imagebyte[m] = 0;
                    else
                        Imagebyte[m] = 255;
                    m++;
                }
            }
        }
        fwrite(Imagebyte, sizeof(unsigned char), Image.Size, life);
        fclose(life);
    }

    // Освобождение памяти
    for (i = 0; i < Image.Height; i++) {
        free(world[i]);
    }
    free(world);

    return 0;
}
