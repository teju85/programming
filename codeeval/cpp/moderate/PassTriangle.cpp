//
// Challenge name: Pass Triangle
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/89/
// Compile       : g++ -Wall -g -o PassTriangle PassTriangle.cpp
//

#include <stdio.h>
#define MAX_LEN 4096
int array[MAX_LEN];
int numRows;

template <typename T>
T sqrtInt(T in) {
    T out;
    in = (in + 1) >> 1;
    for(out=0;in>out;in-=out++);
    return out;
}

void findNumRows(int len) {
    int s = sqrtInt((len << 3) + 1);
    numRows = ((s - 1) >> 1);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: PassTriangle <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    int len = 0;
    while(!feof(fp)) {
        if(fscanf(fp, "%d", &(array[len])) <= 0) {
            break;
        }
        ++len;
    }
    fclose(fp);
    findNumRows(len);
    for(int i=numRows-2;i>=0;--i) {
        int start = (i * (i + 1)) >> 1;
        int belowStart = start + i + 1;
        for(int j=0;j<=i;++j) {
            int idx = start + j;
            int below = belowStart + j;
            int a = array[below];
            int b = array[below+1];
            array[idx] += (a > b)? a : b;
        }
    }
    printf("%d\n", array[0]);
    return 0;
}
