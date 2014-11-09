//
// Challenge name: Calculate Distance
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/99/
// Compile       : g++ -Wall -g -o CalculateDistance CalculateDistance.cpp
//

#include <stdio.h>

template <typename T>
T sqrtInt(T in) {
    T out;
    in = (in + 1) >> 1;
    for(out=0;in>out;in-=out++);
    return out;
}

int distance(int x1, int y1, int x2, int y2) {
    int a = (x1 - x2);
    int b = (y1 - y2);
    int dist = (a * a) + (b * b);
    return sqrtInt(dist);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: CalculateDistance <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int x1, y1, x2, y2;
        if(fscanf(fp, "(%d, %d) (%d, %d)\n", &x1, &y1, &x2, &y2) != 4) {
            continue;
        }
        printf("%d\n", distance(x1, y1, x2, y2));
    }
    fclose(fp);
    return 0;
}
