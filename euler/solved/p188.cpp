//
// Challenge name: Problem 188
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=188
// Compile       : g++ -Wall -g -o p188 p188.cpp
// Run           : ./p188
//

#include <stdio.h>
#include "include/integers.h"

#define INT long long int


/**
 * @brief finds the value of the equation:  a^^k % m
 * @param a number
 * @param k hyper-exponent
 * @param m modulo number
 * Assumption: gcd(a, m) = 1
 */
INT modularTetration(INT a, INT k, INT m) {
    // trivial cases
    if((m <= 1) || (a <= 0)) {
        return 0;
    }
    if((k <= 0) || (a == 1)) {
        return 1;
    }
    if(k == 1) {
        return (a % m);
    }
    INT phi = euler_totient<INT>(m);
    INT pow = modularTetration(a, k-1, phi);
    INT mod = 1;
    for(int i=0;i<pow;++i) {
        mod = (mod * a) % m;
    }
    return mod;
}

int main(int argc, char** argv) {
    printf("%lld\n", modularTetration(1777, 1855, 100000000));
    return 0;
}
