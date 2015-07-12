//
// Challenge name: Compare Points
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/192/
// Compile       : g++ -Wall -g -o ComparePoints ComparePoints.cpp
//

#include <stdio.h>

void direction(int o, int p, int q, int r) {
    int delx = q - o;
    int dely = r - p;
    if(delx > 0) {
        if(dely > 0) {
            printf("NE\n");
        }
        else if(dely < 0) {
            printf("SE\n");
        }
        else {
            printf("E\n");
        }
    }
    else if(delx < 0) {
        if(dely > 0) {
            printf("NW\n");
        }
        else if(dely < 0) {
            printf("SW\n");
        }
        else {
            printf("W\n");
        }
    }
    else {
        if(dely > 0) {
            printf("N\n");
        }
        else if(dely < 0) {
            printf("S\n");
        }
        else {
            printf("here\n");
        }
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: ComparePoints <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int o, p, q, r;
        if(fscanf(fp, "%d%d%d%d", &o, &p, &q, &r) != 4) {
            continue;
        }
        direction(o, p, q, r);
    }
    fclose(fp);
    return 0;
}
