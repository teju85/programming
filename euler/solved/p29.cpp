//
// Challenge name: Problem 29
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=29
// Compile       : g++ -Wall -g -o p29 p29.cpp
// Run           : ./p29
//

#include <stdio.h>
#include "include/integers.h"
#define LIMIT 100
#define INT long long int

INT matrix[LIMIT+1][LIMIT+1];

void initialize() {
    for(INT a=2;a<=LIMIT;++a) {
        for(INT b=2;b<=LIMIT;++b) {
            matrix[a][b] = 1;
        }
    }
}

void mark_duplicate(INT a, INT b, INT c, INT d) {
    if(b == d) {
        return;
    }
    if(a == c) {
        return;
    }
    if((a > LIMIT) || (b > LIMIT) || (c > LIMIT) || (d > LIMIT)) {
        return;
    }
    //printf("a=%lld b=%lld c=%lld d=%lld\n", a, b, c, d);
    matrix[c][d] = 0;
}


/**
 * If a^b = c^d  (a < c), then
 *   a = x^e  and  c = x^f  and   be = df
 */

int main(int argc, char** argv) {
    INT sqa = sqrt_int<INT>(LIMIT);
    initialize();
    for(INT a=2;a<=sqa;++a) {
        for(INT c=a*a,x=2;c<=LIMIT;++x,c*=a) {
            for(INT b=x<<1,d=2;d<=LIMIT;b+=x,++d) {
                // we could get higher powers in the range!
                if(b > LIMIT) {
                    INT k = b;
                    // factors of 'b' for which we can get higher powers
                    for(INT j=2,aa=a*a;j<k;++j,aa*=a) {
                        if((aa > LIMIT) || (aa >= c)) {
                            break;
                        }
                        if(b % j) {
                            continue;
                        }
                        k = b / j;
                        mark_duplicate(aa, k, c, d);
                    }
                }
                else {
                    mark_duplicate(a, b, c, d);
                }
            }
        }
    }
    INT total = 0;
    for(INT a=2;a<=LIMIT;++a) {
        for(INT b=2;b<=LIMIT;++b) {
            total += matrix[a][b];
        }
    }
    printf("%lld\n", total);
    return 0;
}
