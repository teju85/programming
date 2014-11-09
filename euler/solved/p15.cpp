//
// Challenge name: Problem 15
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=15
// Compile       : g++ -Wall -g -o p15 p15.cpp
// Run           : ./p15
//

#include <stdio.h>
#define DIM 20
#define INT unsigned long long int

INT paths[DIM+1][DIM+1];

void initialize() {
    paths[0][0] = 0;
    for(INT i=1;i<=DIM;++i) {
        paths[i][0] = 1;
        paths[0][i] = 1;
    }
}

int main(int argc, char** argv) {
    initialize();
    for(INT i=1;i<=DIM;++i) {
        for(INT j=1;j<=DIM;++j) {
            paths[i][j] = paths[i-1][j] + paths[i][j-1];
        }
    }
    printf("%llu\n", paths[DIM][DIM]);
    return 0;
}
