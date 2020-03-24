#include <stdio.h>

void filecopy(FILE *from, FILE *to) {
    unsigned char c;
    while (!feof(from)) {
        fread (&c,1,1,from);
        fwrite (&c,1,1,to);
    }
}
int main(int argc, char* ptt[]) {
    FILE *in1, *in2, *in3;
    in1 = fopen(ptt[1],"r");
    in3 = fopen(ptt[3],"w");
    filecopy(in1, in3);
    fclose(in1);
    in2 = fopen(ptt[2],"r");
    filecopy(in2,in3);
    fclose(in2);
    fclose(in3);
    return 0;
}