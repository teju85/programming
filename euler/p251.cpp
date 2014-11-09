//
// Challenge name: Problem 251
// Difficulty    : hard
// Link          : http://projecteuler.net/index.php?section=problems&id=251
// Compile       : g++ -Wall -g -o p251 p251.cpp -lm
// Run           : ./p251
//

#include <stdio.h>
#include <math.h>
#include "include/integers.h"
#define INT unsigned long long int
#define MAX 110000ULL

/**
 * The equation for cardano triplets can be reduced to:
 *   8a^3 + 15a^2 + 6a - 1  =  27cb^2
 *
 * Simplifying the LHS, leads to:
 *   ((a + 1)^2 * (8a - 1)) / 27   =  c * b^2
 *
 * Implies, a = 2 mod 3
 */

INT isqrt(INT in) {
    double v = (double) in;
    return (INT)sqrt(v);
}

INT numTriplets() {
    INT num = 0;
    for(INT a=2;a<MAX;a+=3) {
        INT t1 = (a + 1) / 3;
        INT t2 = ((a << 3) - 1) / 3;
        INT lhs = t1 * t1 * t2;
    }
    return num;
}

int main(int argc, char** argv) {
    printf("%llu\n", numTriplets());
    printf("%llu\n", MAX * MAX * MAX);
    return 0;
    INT a, b, c;
    INT t, S, x, sq, max;
    INT num = 0;
    for(a=MAX-2;a>0;--a) {
        t = (a + 1);
        t = (t * t * ((a << 3) - 1));
        if(t % 27) {
            continue;
        }
        t /= 27;
        S = MAX - a;
        sq = isqrt(t);
        max = (S < sq)? S : sq;
        x = t / (max * max);
        if(x > S) {
            continue;
        }
        for(b=max;b>0;--b) {
            x = b * b;
            if(t % x) {
                continue;
            }
            c = t / x;
            if(c > S) {
                break;
            }
            else if(c <= S - b) {
                //printf("%llu %llu %llu\n", a, b, c);
                ++num;
            }
        }
        if(!(a % 1000)) {
            printf("%llu %llu %llu %llu %llu %llu\n", a, max, S, sq, t, num);
        }
    }
    printf("%llu\n", num);
    return 0;
}



/*

INT num = 1;  // a=2, is considered a trivial solution here!

void checkNumbers(INT a, INT b, INT c) {
    if((a + b + c) <= MAX) {
        ++num;
        printf("%llu %llu %llu\n", a, b, c);
    }
}

int main(int argc, char** argv) {
    INT a, b, c;
    INT c1, b1, j, k, t;
    for(a=MAX-2;a>2;--a) {
        if((a % 3) != 2) {
            continue;
        }
        b = (a + 1) / 3;
        c = ((a << 3) - 1) / 3;
        //printf(" --- %llu %llu %llu\n", a, b, c);
        // factors of 'b'
        for(j=1,k=b;j<k;++j) {
            if(!(b % j)) {
                k = b / j;
                if(k > j) {
                    c1 = j * j * c;
                    checkNumbers(a, k, c1);
                    c1 = k * k * c;
                    checkNumbers(a, j, c1);
                }
                else if(k == j) {
                    c1 = j * j * c;
                    checkNumbers(a, k, c1);
                }
            }
        }
        // square factors of 'c'
        for(j=2,k=c;j<k;++j) {
            if(!(c % j)) {
                k = c / j;
                t = sqrt_int<INT>(j);
                if((t * t) == j) {
                    b1 = t * b;
                    checkNumbers(a, b1, k);
                }
            }
        }
    }
    printf("%llu\n", num);
    return 0;
}
*/
