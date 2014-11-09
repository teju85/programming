//
// Challenge name: Problem 28
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=28
// Compile       : g++ -Wall -g -o p28 p28.cpp
// Run           : ./p28
//

#include <stdio.h>
#define DIM 1001
#define INT unsigned int

int main(int argc, char** argv) {
    INT sum = 1; // center is always one!
    // for a given number, the four corners will be
    //  right-top    = n^2
    //  left-top     = n^2 - (n-1)
    //  left-bottom  = n^2 - 2*(n-1)
    //  right-bottom = n^2 - 3*(n-1)
    //  summation = 4*n^2 - 6*(n-1)
    for(INT n=3;n<=1001;n+=2) { // only odd numbered dimensions possible!
        INT val = ((n * n) << 2) - (6 * (n - 1));
        sum += val;
    }
    printf("%u\n", sum);
    return 0;
}
