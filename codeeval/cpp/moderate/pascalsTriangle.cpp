//
// Challenge name: Pascals Triangle
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/66/
// Compile       : g++ -Wall -g -o pascalsTriangle pascalsTriangle.cpp
//

#include <stdio.h>

int evalNCR(int ncr1, int r, int n) {
    if((r == 0) || (r == n)) {
        return 1;
    }
    --r;
    return ((ncr1 * (n - r)) / (r + 1));
}

void printPascalsTriangle(int num) {
    printf("1");
    for(int n=1;n<num;++n) {
        int ncr = 0;
        for(int r=0;r<=n;++r) {
            ncr = evalNCR(ncr, r, n);
            printf(" %d", ncr);
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: pascalsTriangle <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int num = 0;
        fscanf(fp, "%d", &num);
        if(num <= 0) {
            continue;
        }
        printPascalsTriangle(num);
    }
    fclose(fp);
    return 0;
}
