//
// Challenge name: Problem 43
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=43
// Compile       : g++ -Wall -g -o p43 p43.cpp
// Run           : ./p43
//

#include <stdio.h>
#include "include/permute.h"

#define INT long long int
#define DIGITS 10

INT getInt(const char* data, int s, int e) {
    INT sum = 0;
    for(INT i=e,j=1;i>=s;--i,j*=10) {
        sum += (data[i] * j);
    }
    return sum;
}

INT primes[] = { 2, 3, 5, 7, 11, 13, 17 };
INT numPrimes = 7;

int main(int argc, char** argv) {
    Permute p(DIGITS);
    const char* data;
    INT sum = 0;
    while((data = p.next(false)) != NULL) {
        // primes can't be even
        // (and we start counting from 'DIGITS-1' in this problem)
        if(!(data[DIGITS-1] & 0x1)) {
            continue;
        }
        INT i;
        for(i=0;i<numPrimes;++i) {
            INT val = getInt(data, i+1, i+3);
            if(val % primes[i]) {
                break;
            }
        }
        if(i >= numPrimes) {
            INT val = getInt(data, 0, DIGITS-1);
            sum += val;
            printf("%lld\n", val);
        }
    }
    printf("sum=%lld\n", sum);
    return 0;
}
