//
// Challenge name: Problem 182
// Difficulty    : hard
// Link          : http://projecteuler.net/index.php?section=problems&id=182
// Compile       : g++ -Wall -g -o p182 p182.cpp
// Run           : ./p182
//

#include <stdio.h>
#include "include/integers.h"
#define P 1009ULL
#define Q 3643ULL
#define INT unsigned long long int

int main(int argc, char** argv) {
    INT p1 = P - 1;
    INT q1 = Q - 1;
    INT phi = p1 * q1;
    INT sum = 0;
    // 'e' has to be odd
    for(INT e=3;e<phi;e+=2) {
        if(gcd<INT>(e, phi) != 1) {
            continue;
        }
        if(gcd<INT>(e-1, p1) != 2) {
            continue;
        }
        if(gcd<INT>(e-1, q1) != 2) {
            continue;
        }
        sum += e;
        //printf("%llu %llu\n", e, sum);
    }
    printf("%llu\n", sum);
    return 0;
}
