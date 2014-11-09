//
// Challenge name: Problem 187
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=187
// Compile       : g++ -Wall -g -o p187 p187.cpp
// Run           : ./p187
//

#include <stdio.h>
#include "include/seive.h"

#define LIMIT 100000000

int main(int argc, char** argv) {
    int num = 0;
    eratos se(LIMIT);
    se.generate_seive();
    for(int i=2;i<LIMIT;++i) {
        if(! se.is_prime(i)) {
            continue;
        }
        int lim = LIMIT / i;
        for(int j=i;j<=lim;++j) {
            if(se.is_prime(j)) {
                ++num;
            }
        }
    }
    printf("%d\n", num);
    return 0;
}
