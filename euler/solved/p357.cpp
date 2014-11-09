//
// Challenge name: Problem 357
// Difficulty    : hard
// Link          : http://projecteuler.net/index.php?section=problems&id=357
// Compile       : g++ -Wall -g -o p357 p357.cpp
// Run           : ./p357
//

#include <stdio.h>

#include "include/integers.h"
#include "include/seive.h"

#define LIMIT 100000000


int prime_seive[LIMIT+1];



bool divisors_test(int a, const eratos& se) {
    for(int j=3,k=a/3;j<=k;++j) {
        k = a / j;
        if((a % j) == 0) {
            if(! se.is_prime((uint32)(j + k))) {
                return false;
            }
        }
    }
    return true;
}

void initialize_prime_seive(const eratos& se) {
    prime_seive[0] = 0;
    prime_seive[1] = 1;
    prime_seive[2] = 1;
    for(int i=3;i<=LIMIT;++i) {
        prime_seive[i] = se.is_prime(i+1);
    }
}

void prime_square_seive(const eratos& se) {
    int lmt = sqrt_int<int>(LIMIT);
    for(int i=2;i<=lmt;++i) {
        if(! se.is_prime(i)) {
            continue;
        }
        int sq = i * i;
        for(int j=sq;j<=LIMIT;j+=sq) {
            prime_seive[j] = 0;
        }
    }
}

int main(int argc, char** argv) {
    // seive of eratosthenes
    eratos se(LIMIT + 100); // +100 to be safe
    se.generate_seive();
    // number is eligible only if num+1 is prime!
    initialize_prime_seive(se);
    // eliminate all numbers having powers of prime to be one of its divisors
    prime_square_seive(se);
    unsigned long long int sum = 3;  // 1, 2 are such numbers
    for(int i=3;i<=LIMIT;++i) {
        if(!prime_seive[i]) {
            continue;
        }
        if(!se.is_prime((i + 4) >> 1)) {
            continue;
        }
        bool flag = divisors_test(i, se);
        //printf("%d => %d\n", i, flag);
        if(flag) {
            sum += i;
        }
    }
    printf("%llu\n", sum);
    return 0;
}
