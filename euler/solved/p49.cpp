//
// Challenge name: Problem 49
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=49
// Compile       : g++ -Wall -g -o p49 p49.cpp
// Run           : ./p49
//

#include <stdio.h>
#include "include/seive.h"
#include "include/integers.h"
#define LIMIT 10000
#define DEL 3330
#define INT int


int main(int argc, char** argv) {
    eratos se(LIMIT*10);
    se.generate_seive();
    INT limit = LIMIT - 3330;
    for(INT i=1001;i<=limit;i+=2) {
        if(!se.is_prime(i)) {
            continue;
        }
        INT i2 = i + DEL;
        INT i3 = i2 + DEL;
        if(se.is_prime(i2) && se.is_prime(i3)) {
            if(is_permutation<INT>(i, i2) && is_permutation<INT>(i, i3)) {
                printf("%d%d%d\n", i, i2, i3);
            }
        }
    }
    return 0;
}
