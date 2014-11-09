//
// Challenge name: Problem 14
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=14
// Compile       : g++ -Wall -g -o p14 p14.cpp
// Run           : ./p14
//

#include <stdio.h>
#define LIMIT 1000000ULL
#define INT unsigned long long int
INT numSteps[LIMIT+1];


INT collatz(INT n) {
    return ((n & 0x1ULL)? ((3ULL * n) + 1ULL) : (n >> 1ULL));
}

INT num_steps(INT num) {
    if(num <= 0ULL) {
        return 0ULL;
    }
    INT steps = 1ULL;
    while(num != 1ULL) {
        num = collatz(num);
        ++steps;
    }
    return steps;
}

int main(int argc, char** argv) {
    INT max = 0ULL;
    INT num = 0ULL;
    for(INT i=1ULL;i<=LIMIT;++i) {
        INT steps = num_steps(i);
        if(steps > max) {
            max = steps;
            num = i;
        }
    }
    printf("max-steps=%llu num=%llu\n", max, num);
    return 0;
}
