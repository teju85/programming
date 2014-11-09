//
// Challenge name: Problem 5
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=5
// Compile       : g++ -Wall -g -o p5 p5.cpp
// Run           : ./p5
//

#include <stdio.h>
#include "include/integers.h"

#define INT unsigned long long int

int main(int argc, char** argv) {
    INT lcd = lcm<INT>(1ULL, 2ULL);
    INT max = 20ULL;
    for(INT num=3;num<=max;++num) {
        lcd = lcm<INT>(lcd, num);
    }
    printf("%llu\n", lcd);
    return 0;
}
