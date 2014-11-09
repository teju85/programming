//
// Challenge name: Problem 10
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=10
// Compile       : g++ -Wall -g -o p10 p10.cpp
// Run           : ./p10
//

#include <stdio.h>
#include "include/seive.h"
#define INT unsigned long long int
#define MAX 2000000

int main(int argc, char** argv) {
    eratos sev(MAX);
    INT sum = 2ULL;
    for(uint32 i=3;i<=MAX;i+=2) {
        if(sev.is_prime(i)) {
            sum += (INT)i;
        }
    }
    printf("%llu\n", sum);
    return 0;
}
