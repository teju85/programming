//
// Challenge name: Problem 27
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=27
// Compile       : g++ -Wall -g -o p27 p27.cpp
// Run           : ./p27
//

#include <stdio.h>
#include "include/integers.h"
#include "include/seive.h"
#define LIMIT 1000
#define MAX 10000000
#define INT long long int


INT consecutive_primes(INT a, INT b, const eratos& se) {
    INT n = 0;
    for(n=0;;++n) {
        INT num = (n * n) + (a * n) + b;
        if(num < 0) {
            num = -num;
        }
        if(num >= MAX) {
            if(!is_prime<INT>(num)) {
                return n;
            }
        }
        else {
            if(!se.is_prime(num)) {
                return n;
            }
        }
    }
    return n;
}

void find_num_primes(INT a, INT b, const eratos& se, INT& max, INT& maxa,
                     INT& maxb) {
    INT num;
    num = consecutive_primes(a, b, se);
    if(num > max) {
        max = num;
        maxa = a;
        maxb = b;
    }
    num = consecutive_primes(a, -b, se);
    if(num > max) {
        max = num;
        maxa = a;
        maxb = -b;
    }
    num = consecutive_primes(-a, b, se);
    if(num > max) {
        max = num;
        maxa = -a;
        maxb = b;
    }
    num = consecutive_primes(-a, -b, se);
    if(num > max) {
        max = num;
        maxa = -a;
        maxb = -b;
    }
}

int main(int argc, char** argv) {
    eratos se(MAX);
    se.generate_seive();
    INT max = 0;
    INT maxa = 0;
    INT maxb = 0;
    for(INT a=1;a<=LIMIT;a+=2) {
        find_num_primes(a, 2, se, max, maxa, maxb);
        for(INT b=2;b<=LIMIT;++b) {
            if(se.is_prime(b)) {
                find_num_primes(a, b, se, max, maxa, maxb);
            }
        }
    }
    printf("a=%lld b=%lld max=%lld prod=%lld\n",
           maxa, maxb, max, (maxa * maxb));
    return 0;
}
