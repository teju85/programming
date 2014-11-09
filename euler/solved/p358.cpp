//
// Challenge name: Problem 358
// Difficulty    : hard
// Link          : http://projecteuler.net/index.php?section=problems&id=358
// Compile       : g++ -Wall -g -o p358 p358.cpp
// Run           : ./p358
//

#include <stdio.h>

#include "include/integers.h"

#define INT long long int




int main(int argc, char** argv) {
    INT high = 729927007LL;   // inverse of 0.00000000137
    INT low  = 724637681LL;   // inverse of 0.00000000138

    ////// Finding the prime 'p' //////
    // cyclic numbers (in base 10) are always of the form
    //    (10^(p-1) - 1) / p    p = a prime number
    // Given: last 5 digits = 56789
    //  => (m * p) = (10^(p-1) - 1)
    //  => (m * p) % 100000 = 99999
    //  => (56789 * p) % 100000 = 99999
    INT p;
    for(p=high;p>=low;p-=2) {
        if(! is_prime<INT>(p)) {
            continue;
        }
        INT t = (56789 * p) % 100000;
        if(t != 99999) {
            continue;
        }
        printf("prime is %lld\n", p);
        // sum of digits of a cyclic number is 9 * (p - 1) / 2
        // From Midy's Theorem
        INT sum = 9 * ((p - 1) >> 1);
        printf("Sum of digits %lld\n", sum);
        break;
    }
    return 0;
}
