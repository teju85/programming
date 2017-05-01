//
// Challenge name: ONE ZERO, TWO ZEROS...
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/217/
// Compile       : g++ -Wall -g -o OneZeroTwoZeros OneZeroTwoZeros.cpp
//

#include <stdio.h>

int numConsecZeros(int num) {
    int c = 0;
    for(;num!=0;num>>=1) {
        int lastBit = num & 1;
        if(!lastBit) {
            ++c;
        }
    }
    return c;
}

int count(int nZeros, int N) {
    int num = 0;
    for(int i=1;i<=N;++i) {
        if(numConsecZeros(i) == nZeros) {
            ++num;
        }
    }
    return num;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: OneZeroTwoZeros <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int nZeros, N;
        if(fscanf(fp, "%d%d", &nZeros, &N) != 2) {
            continue;
        }
        printf("%d\n", count(nZeros, N));
    }
    fclose(fp);
    return 0;
}
