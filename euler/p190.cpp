//
// Challenge name: Problem 190
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=190
// Compile       : g++ -Wall -g -o p190 p190.cpp -lm
// Run           : ./p190
//

#include <stdio.h>
#include <math.h>

#define INT long long int


INT solveForPm(int m) {
    float pm = 1;
    for(int i=1;i<=m;++i) {
        float xi = (2.0f * i) / (m + 1);
        pm *= pow(xi, i);
    }
    return ((INT) floor(pm));
}

int main(int argc, char** argv) {
    INT sum = 0;
    for(int m=2;m<=15;++m) {
        int pm = solveForPm(m);
        sum += (INT)pm;
        printf("m=%d [pm]=%d\n", m, pm);
    }
    printf("sum=%lld\n", sum);
    return 0;
}
