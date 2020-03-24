#include <stdio.h>

void create(char* arcname, int cnt, char* files[]) {
    FILE* arcfile = fopen(arcname, "wb");
    FILE* file;
    unsigned long long int nameandsize[128];
    for (int i = 5; i < cnt; i++){
        file = fopen(files[i], "rb");
        fseek(file, 0, SEEK_END);
        nameandsize[i - 5] = ftell(file);
        fclose(file);
    }
    for (int i = 0; i < cnt - 5; i++)
        fprintf(arcfile, "( %s : %llu )", files[i + 5], nameandsize[i]);
    fprintf(arcfile, "\n");
    for (int i = 5; i < cnt; i++){
        file = fopen(files[i], "rb");
        int temp;
        while ((temp = getc(file)) != EOF)
            putc(temp, arcfile);
        fclose(file);
    }
}

void extract(char* arcname){
    FILE* arc = fopen(arcname, "rb+wb");
    unsigned long long int  startpos = 0;
    int c;
    while ((c = getc(arc)) != EOF) {
        startpos++;
        if (c == '\n') break;
    }
    fseek(arc, 0, SEEK_SET);
    char filename[128] = {0};
    unsigned long long int  filesize;
    FILE *file;
    unsigned long long int  nowpos = 0;
    while (fscanf(arc, "( %s : %llu )", filename, &filesize) != 0) {
        file = fopen(filename, "wb");
        nowpos = ftell(arc);
        fseek(arc, startpos, SEEK_SET);
        startpos += filesize;
        while (filesize-- > 0) putc((c = getc(arc)), file);
        fseek(arc, nowpos, SEEK_SET);
        fclose(file);
    }
}

void list(char* arcname){
    FILE* arc = fopen(arcname, "rb");
    char filename[128] = {0};
    unsigned long long int  filesize;
    while (fscanf(arc, "( %s : %llu )", filename, &filesize) != 0) printf("\t%s\n", filename);
    fclose(arc);
}

int main(int argc, char *argv[]) {
    FILE* arc;
    char* arcname;
    for (int i = 0; i < argc; i++){
        if(argv[i][2] == 'f') arcname = argv[i + 1];
        if(argv[i][2] == 'c' && argv[i][1] == '-') create(arcname, argc, argv);
        if(argv[i][2] == 'e') extract(arcname);
        if(argv[i][2] == 'l') list(arcname);
    }
    return 0;
}