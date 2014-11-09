//
// Challenge name: Problem 71
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=71
// Compile       : g++ -Wall -g -o p71 p71.cpp
// Run           : ./p71
//

#include <stdio.h>
#include "include/integers.h"
#define INT int
#define LIMIT 1000000
#define NUME 3
#define DENO 7


void reduce(INT& num, INT& den) {
    INT g = gcd<INT>(num, den);
    num /= g;
    den /= g;
}

int main(int argc, char** argv) {
    float rat = ((float)NUME) / DENO;
    float min = rat / 3;
    INT minn = 0;
    INT mind = 0;
    for(INT d=LIMIT,ii=0;ii<100;++ii,--d) {
        INT limit = (INT) (rat * d);
        ++limit;
        INT start = (INT) ((rat-min) * d);
        --start;
        if(start <= 0) {
            start = 1;
        }
        for(INT n=start;n<=limit;++n) {
            INT n1 = n;
            INT d1 = d;
            reduce(n1, d1);
            if((n1 == NUME) && (d1 == DENO)) {
                continue;
            }
            float r = ((float)n) / d;
            float diff = rat - r;
            if((diff > 0) && (diff < min)) {
                min = diff;
                minn = n;
                mind = d;
            }
        }
    }
    printf("Before reduction rat=%f n=%d d=%d r=%f\n", rat, minn, mind, min);
    reduce(minn, mind);
    printf("After reduction rat=%f n=%d d=%d r=%f\n", rat, minn, mind, min);
    return 0;
}
