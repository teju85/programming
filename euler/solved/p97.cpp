//
// Challenge name: Problem 97
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=97
// Compile       : g++ -Wall -g -o p97 p97.cpp
// Run           : ./p97
//

#include <stdio.h>
#define NUM 10000000000ULL
#define INT unsigned long long int

int main(int argc, char** argv) {
    INT exp = 7830457ULL;
    INT mult = 28433ULL;
    INT po2 = 1ULL;
    for(INT i=1;i<=exp;++i) {
        po2 <<= 1;
        if(po2 >= NUM) {
            po2 %= NUM;
        }
    }
    po2 = (mult * po2) % NUM;
    po2 = (po2 + 1) % NUM;
    printf("%llu\n", po2);
    return 0;
}
