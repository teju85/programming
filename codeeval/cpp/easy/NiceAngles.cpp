//
// Challenge name: NiceAngles
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/160/
// Compile       : g++ -Wall -g -o NiceAngles NiceAngles.cpp
//

#include <stdio.h>

void niceAngles(float an) {
    int d = (int) an;
    int m = (int) ((an - d) * 60.0f);
    int s = (int) ((an - d - (m / 60.0f)) * 3600.0f);
    printf("%d.%02d'%02d\"\n", d, m, s);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: NiceAngles <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        float an;
        if(fscanf(fp, "%f", &an) != 1) {
            continue;
        }
        niceAngles(an);
    }
    fclose(fp);
    return 0;
}
