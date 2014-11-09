//
// Challenge name: Problem 37
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=37
// Compile       : g++ -Wall -g -o p37 p37.cpp
// Run           : ./p37
//

#include <stdio.h>
#include "include/seive.h"

#define LIMIT 10000000

bool truncatablePrime(int num, const eratos& se) {
    if(!se.is_prime(num)) {
        return false;
    }
    for(int m=10;;m*=10) {
        int q = num / m;
        int r = num % m;
        if(!q) {
            break;
        }
        if(!se.is_prime(q) || !se.is_prime(r)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    eratos se(LIMIT);
    se.generate_seive();
    int num, sum;
    num = sum = 0;
    for(int i=11;;i+=2) {
        if(truncatablePrime(i, se)) {
            sum += i;
            ++num;
            printf("%d\n", i);
        }
        if(num == 11) { // given: there are only 11 such numbers
            break;
        }
    }
    printf("Sum=%d\n", sum);
    return 0;
}
