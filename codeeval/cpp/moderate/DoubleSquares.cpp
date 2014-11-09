//
// Challenge name: Double Squares
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/33/
// Compile       : g++ -Wall -g -o DoubleSquares DoubleSquares.cpp
//

#include <stdio.h>
#define MAX_TESTS 100
#define MAX_RANGE 2147483647
#define SQ_MAX_RANGE 46343  // ceil(sqrt(MX_RANGE)) + 2
unsigned int squares[SQ_MAX_RANGE];


unsigned int _sqroot(unsigned int in, int s, int e) {
    if(s >= e) {
        return (unsigned int) s;
    }
    int mid = (s + e) >> 1;
    if((mid == s) || (mid == e)) {
        return (unsigned int)mid;
    }
    if(squares[mid] > in) {
        return _sqroot(in, s, mid);
    }
    else if(squares[mid] < in) {
        return _sqroot(in, mid, e);
    }
    else {
        return (unsigned int)mid;
    }
}
unsigned int sqroot(unsigned int in) {
    return _sqroot(in, 0, SQ_MAX_RANGE-1);
}


int main(int argc, char** argv) {
    FILE* fp;
    int numTests, i, found;
    unsigned int X, sqX, j, loc;
    if(argc != 2) {
        printf("USAGE: DoubleSquares <fileContainingTestVectors>\n");
        return 1;
    }
    for(i=0;i<SQ_MAX_RANGE;i++) {
        squares[i] = i * i;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    fscanf(fp, "%d", &numTests);
    for(i=0;i<numTests;i++) {
        fscanf(fp, "%u", &X);
        if(X == 0) {
            printf("1\n");
            continue;
        }
        found = 0;
        sqX = sqroot(X>>1);
        for(j=0;j<=sqX;j++) {
            if(X < squares[j]) {
                continue;
            }
            loc = sqroot(X - squares[j]);
            if(X == (squares[j] + squares[loc])) {
                found++;
            }
        }
        printf("%d\n", found);
    }
    fclose(fp);
    return 0;
}
