//
// Challenge name: Problem 25
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=25
// Compile       : g++ -Wall -g -o p25 p25.cpp -lm
// Run           : ./p25
//

#include <stdio.h>
#include <math.h>

#define DIGITS 1000


int main(int argc, char** argv) {
    double sqr5 = sqrt(5.0);
    double phi = (1 + sqr5) / 2;
    double lsqr5 = log10(sqr5);
    double lphi = log10(phi);
    double n = ceil((DIGITS - 1 + lsqr5) / lphi);
    printf("%lf\n", n);
    return 0;
}
