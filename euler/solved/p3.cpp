//
// Challenge name: Problem 3
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=3
// Compile       : g++ -Wall -g -o p3 p3.cpp
// Run           : ./p3
//

#include <stdio.h>
#include "include/integers.h"
#define NUM 600851475143ULL
#define INT unsigned long long int


int main(int argc, char** argv) {
    INT sq = sqrt_int<INT>(NUM);
    if(!(sq & 1ULL)) {
        ++sq;
    }
    for(;sq>2;sq-=2) {
        if(NUM % sq) {
            continue;
        }
        if(is_prime<INT>(sq)) {
            break;
        }
    }
    printf("%llu\n", sq);
    return 0;
}
