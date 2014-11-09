//
// Challenge name: Problem 72
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=72
// Compile       : g++ -Wall -g -o p72 p72.cpp
// Run           : ./p72
//

#include <stdio.h>
#define INT long long int
#define TOTIENT_INT INT
#include "include/totient.h"
#define LIMIT 1000000

int main(int argc, char** argv) {
    EulerTotient et(LIMIT);
    INT num = 0;
    for(INT n=2;n<=LIMIT;++n) {
        num += et.get_totient(n);
    }
    printf("total=%lld\n", num);
    return 0;
}
