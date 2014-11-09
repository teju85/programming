//
// Challenge name: Problem 58
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=58
// Compile       : g++ -Wall -g -o p58 p58.cpp
// Run           : ./p58
//

#include <stdio.h>
#include "include/integers.h"
#define RATIO 0.1f
#define INT unsigned int


int main(int argc, char** argv) {
    INT total = 1;
    INT numPrimes = 0;
    for(INT side=3;;side+=2) { // length will also be odd!
        total += 4;
        INT del = side - 1;
        for(INT i=1,num=(side*side)-del;i<=3;++i,num-=del) {
            if(is_prime<INT>(num)) {
                ++numPrimes;
            }
        }
        float ratio = ((float)numPrimes) / total;
        if(ratio < RATIO) {
            printf("side=%u ratio=%f\n", side, ratio);
            break;
        }
    }
    return 0;
}
