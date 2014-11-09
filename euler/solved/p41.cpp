//
// Challenge name: Problem 41
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=41
// Compile       : g++ -Wall -g -o p41 p41.cpp
// Run           : ./p41
//

#include <stdio.h>
#include "include/permute.h"

/**
 * All 9 and 8 digit numbers are divisible by 9
 */
#define DIGITS 7
#define INT long long int

INT getInt(const char* data) {
    INT sum = 0;
    for(INT i=0,j=1;i<DIGITS;++i,j*=10) {
        sum += ((data[i] + 1) * j);
    }
    return sum;
}

int main(int argc, char** argv) {
    Permute p(DIGITS);
    const char* data;
    INT val;
    while((data = p.next(false)) != NULL) {
        // primes can't be even
        // (and we start counting from '0' in our Permute class)
        if(data[0] & 0x1) {
            continue;
        }
        val = getInt(data);
        if(is_prime<INT>(val)) {
            break;
        }
    }
    printf("%lld\n", val);
    return 0;
}
