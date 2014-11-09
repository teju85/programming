//
// Challenge name: Problem 123
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=123
// Compile       : g++ -Wall -g -o p123 p123.cpp
// Run           : ./p123
//

#include <stdio.h>
#include "include/integers.h"

#define INT unsigned long long int


int main(int argc, char** argv) {
    INT limit = 10000000000ULL;
    INT sqrt_limit = sqrt_int<INT>(limit);
    INT n = 1;
    for(INT pn=3;;pn+=2) {
        if(is_prime<INT>(pn)) {
            ++n;
            INT r1 = 1;
            INT r2 = 1;
            INT pn2 = pn * pn;
            INT n1 = pn - 1;
            INT n2 = pn + 1;
            for(INT i=1;i<=n;++i) {
                r1 = (r1 * n1) % pn2;
                r2 = (r2 * n2) % pn2;
            }
            INT r = (r1 + r2) % pn2;
            if(r >= limit) {
                printf("n=%llu pn=%llu\n", n, pn);
                break;
            }
        }
    }
    return 0;
}
