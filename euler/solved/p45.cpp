//
// Challenge name: Problem 45
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=45
// Compile       : g++ -Wall -g -o p45 p45.cpp
// Run           : ./p45
//

#include <stdio.h>
#include "include/integers.h"
#define INT unsigned long long int
#define START 166

//
// Triangle number:
// Solving n^2 + n - 2*k = 0  ==>  n = (-1 +/- sqrt(1 + 8*k)) / 2
// Now, from this equation, one can easily deduce:
//  . (1 + 8*k) must be a perfect square
//  . sqrt(1 + 8*k) must be odd
//
// Hexagonal number:
// Solving 2*n^2 - n - k = 0  ==>  n = (1 +/- sqrt(1 + 8*k)) / 4
// Now, from this equation, one can easily deduce:
//  . (1 + 8*k) must be a perfect square
//  . sqrt(1 + 8*k) + 1 must be divisible by 4
//
// I'll run through pentagonal numbers, as the conditions for
// Triangle and Hexagonal numbers are similar
//

bool is_tri_hexa(INT num) {
    // (1 + 8*k) must be perfect square
    INT n1 = 1 + (num << 3);
    INT n1_sqrt = sqrt_int<INT>(n1);
    INT n1d = n1_sqrt * n1_sqrt;
    if(n1 != n1d) {
        return false;
    }
    // sqrt must be odd  AND  sqrt+1 must be divisible by 4
    return ((n1_sqrt & 0x1) && !((n1_sqrt + 1) & 0x3));
}

int main(int argc, char** argv) {
    for(INT p=START;;++p) {
        INT pent = (p * ((3 * p) - 1)) >> 1;
        if(is_tri_hexa(pent)) {
            printf("%llu\n", pent);
            break;
        }
    }
    return 0;
}
