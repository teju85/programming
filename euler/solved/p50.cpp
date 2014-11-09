//
// Challenge name: Problem 50
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=50
// Compile       : g++ -Wall -g -o p50 p50.cpp
// Run           : ./p50
//

#include <stdio.h>
#include <vector>
#include "include/seive.h"
#define LIMIT 1000000
#define INT int
using namespace std;

void maxSum(INT s, INT& sum, INT& len, const eratos& se) {
    vector<INT> primes;
    if(s == 2) {
        sum = 2;
        len = 1;
        s = 3;
        primes.push_back(2);
    }
    else {
        sum = 0;
        len = 0;
    }
    for(INT i=s;sum<LIMIT;++i) {
        if(se.is_prime(i)) {
            sum += i;
            ++len;
            primes.push_back(i);
        }
    }
    while(len > 0) {
        --len;
        sum -= primes[len];
        if(se.is_prime(sum)) {
            return;
        }
    }
}

int main(int argc, char** argv) {
    eratos se(LIMIT<<1);
    se.generate_seive();
    INT sum, len;
    maxSum(2, sum, len, se);
    for(INT i=3;i<LIMIT;i+=2) {
        if(!se.is_prime(i)) {
            continue;
        }
        INT s, l;
        maxSum(i, s, l, se);
        //printf("%d %d %d\n", i, s, l);
        if(l > len) {
            sum = s;
            len = l;
        }
    }
    printf("%d %d\n", sum, len);
    return 0;
}
