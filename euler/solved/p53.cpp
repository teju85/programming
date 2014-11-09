//
// Challenge name: Problem 53
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=53
// Compile       : g++ -Wall -g -o p53 p53.cpp
// Run           : ./p53
//

#include <stdio.h>
#define LIMIT 100
#define INT int
#define MAX 1000000

INT ncr[LIMIT+1][LIMIT+1];

void initialize() {
    for(INT n=0;n<=LIMIT;++n) {
        for(INT r=0;r<=LIMIT;++r) {
            ncr[n][r] = 0;
        }
    }
    ncr[0][0] = 1;
    ncr[1][0] = 1;
    ncr[1][1] = 1;
}

int main(int argc, char** argv) {
    INT num = 0;
    initialize();
    for(INT n=2;n<=LIMIT;++n) {
        ncr[n][0] = 1;
        ncr[n][n] = 1;
        for(INT r=1;r<n;++r) {
            INT t = ncr[n-1][r-1] + ncr[n-1][r];
            if(t >= MAX) {
                ++num;
                // once it has reached 'MAX' we don't have to worry about
                // its actual value!
                ncr[n][r] = MAX;
            }
            else {
                ncr[n][r] = t;
            }
        }
    }
    printf("%d\n", num);
    return 0;
}
