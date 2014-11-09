//
// Challenge name: Problem 46
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=46
// Compile       : g++ -Wall -g -o p46 p46.cpp
// Run           : ./p46
//

#include <stdio.h>
#include "include/integers.h"


bool goldbach_conjecture(int num) {
    // smallest prime is 2 and the remaining must be double of a square
    int limit = sqrt_int<int>((num - 2) >> 1);
    for(int i=1;i<=limit;++i) {
        int diff = num - ((i * i) << 1);
        if(diff < 2) {
            return false;
        }
        if(is_prime<int>(diff)) {
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    for(int i=3;;i+=2) {
        if(is_prime(i)) {
            continue;
        }
        if(!goldbach_conjecture(i)) {
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}
