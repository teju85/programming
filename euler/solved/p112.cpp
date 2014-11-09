//
// Challenge name: Problem 112
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=112
// Compile       : g++ -Wall -g -o p112 p112.cpp
// Run           : ./p112
//

#include <stdio.h>

#include "include/bouncy.h"

#define INT unsigned long long int


int main(int argc, char** argv) {
    INT ratio = 99;
    INT numBouncy = 0;
    for(INT n=100;;++n) {
        if(is_bouncy<INT>(n)) {
            ++numBouncy;
            INT t1 = numBouncy * 100;
            if((t1 % n) == 0) {
                INT rat = t1 / n;
                if(rat == ratio) {
                    printf("n=%llu\n", n);
                    break;
                }
            }
        }
    }
    return 0;
}
